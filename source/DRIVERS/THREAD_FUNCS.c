/*
 * THREAD_FUNCS.c
 *
 *  Created on: 8 sep. 2025
 *      Author: Gabriel
 */

#include "THREAD_FUNCS.h"

uint8_t toggle_flag = 0;

void set_toggle_flag(){
	get_PIT_toggle_CB(&toggle_flag);
}

void Thread2ms(void){
	if(toggle_flag == 1){
		cianToggle();
		toggle_flag = 0;
	}

	 if (UART_GetFlag(UART_FLAG_TURN_ON)) {
			/* Prender LED */
			UART_SendString((uint8_t *)"LED ON\r\n");
			redON();
			UART_ClearFlag(UART_FLAG_TURN_ON);
		}
	if (UART_GetFlag(UART_FLAG_TURN_OFF)) {
		/* Apagar LED*/
		UART_SendString((uint8_t *)"LED OFF\r\n");
		redOFF();
		PIT_StopTimer(DEMO_PIT_BASEADDR, PIT_TOGGLE_CHANNEL);
		UART_ClearFlag(UART_FLAG_TURN_OFF);

	}

	if (UART_GetFlag(UART_FLAG_TOGGLE)){

		uint8_t time = UART_GetTime();
		if(time > 0 && time < 6){
			PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, PIT_TOGGLE_CHANNEL, MSEC_TO_COUNT(time*1000, PIT_SOURCE_CLOCK));
			PIT_EnableInterrupts(DEMO_PIT_BASEADDR, PIT_TOGGLE_CHANNEL, kPIT_TimerInterruptEnable);
			PIT_StartTimer(DEMO_PIT_BASEADDR, PIT_TOGGLE_CHANNEL);
		}

		UART_ClearFlag(UART_FLAG_TOGGLE);
	}



	if (UART_GetFlag(UART_FLAG_HELP)){
		UART_Menu();
		UART_ClearFlag(UART_FLAG_HELP);
	}





}

void Thread10ms(void){
	static uint8_t counter = 0;
	static uint16_t adc_value = 0;
	static uint16_t temp = 0;
	counter++;

	// Arreglo circular para temperaturas enteras
	static uint16_t temp_buffer[5] = {0, 0, 0, 0, 0};
    static uint8_t index = 0;

    // Promedio como entero
    static uint16_t temp_promedio = 0;

	if(counter == 2){
		counter = 0;  // Reset del contador
		adc_value = ADC_Read();

		// Conversión a entero: (adc_value * 100) / 4095
		// Para evitar overflow, se puede hacer la división primero si es necesario (mejora sugerida por claudio)
		temp = (uint16_t)((uint32_t)adc_value * 100 / 4095);

		// Guardar lectura en posición actual
		temp_buffer[index] = temp;

		// Mover a siguiente posición
		index++;
		if(index >= 5){
			index = 0;
		}

		// Calcular promedio con aritmética entera
		uint32_t suma = (uint32_t)temp_buffer[0] + temp_buffer[1] + temp_buffer[2] +
						temp_buffer[3] + temp_buffer[4];
		temp_promedio = (uint16_t)(suma / 5);
	}
	temperature = temp_promedio +'0';
	if (UART_GetFlag(UART_FLAG_TEMP)){
		// Mandar promedio de temperatura
		UART_SendString(&temperature);
		UART_ClearFlag(UART_FLAG_TEMP);
	}
}
void Thread5ms(void){
	uint8_t inputSW2= GPIO_PinRead(GPIOC, SW2);


	static uint8_t debounce_counter = 0;

	if (!inputSW2) {
		debounce_counter++;
		if (debounce_counter >= 20) {
			magentaToggle();
			debounce_counter = 0;
		}
	} else {
		debounce_counter = 0;
	}



}
void ThreadIddle(void){
	//ASM(NOP);
}
