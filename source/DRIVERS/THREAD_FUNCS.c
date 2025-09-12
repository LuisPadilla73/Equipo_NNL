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
	static float temp = 0.0f;
	counter++;

	// arreglo circular
	static float temp_buffer[5] = {0, 0, 0, 0, 0};
    static uint8_t index = 0;  // Posición actual en el arreglo
    // promedio
    static float temp_promedio = 0.0f;

	if(counter == 2){
		adc_value = ADC_Read();
		temp = (float) adc_value * 100.0f / 4095.0f;

		/*Guaradar lectura en posición actual*/
		temp_buffer[index] = temp;
		/*Mover siguiente posición*/
		index++;
		if(index >= 5){
			index = 0;
		}

		//promedio.
		temp_promedio = (temp_buffer[0]+temp_buffer[1]+temp_buffer[2]+temp_buffer[3]+
				temp_buffer[4]) / 5.0f;

	}

	if (UART_GetFlag(UART_FLAG_TEMP)){
		//mandar promedio de temp
		UART_SendTemperature(temp_promedio);
		UART_ClearFlag(UART_FLAG_HELP);
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
