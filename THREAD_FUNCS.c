/*
 * THREAD_FUNCS.c
 *
 *  Created on: 8 sep. 2025
 *      Author: Gabriel
 */

#include "THREAD_FUNCS.h"
#include "UART.h"

uint8_t UART_flag_array[];

void Thread2ms(void){
	 if (UART_GetFlag(UART_FLAG_TURN_ON)) {
	        /* Prender LED */
	        UART_SendString((uint8_t *)"LED ON\r\n");
	        UART_ClearFlag(UART_FLAG_TURN_ON);
	    }
	    if (UART_GetFlag(UART_FLAG_TURN_OFF)) {
	        /* Apagar LED*/
	        UART_SendString((uint8_t *)"LED OFF\r\n");
	        UART_ClearFlag(UART_FLAG_TURN_OFF);
	    }

}
void Thread10ms(void){
	static uint8_t counter = 0;
	counter++;

	if(counter == 2){

	}
}
void Thread5ms(void){
	uint8_t inputSW2= GPIO_PinRead(GPIOC, SW2);

	static uint8_t state = init;
	static uint8_t debounce_counter = 0;


	switch(state){
		case init:
			if (!inputSW2) {
			    debounce_counter++;
			    if (debounce_counter >= 20) {
			        state = led_button;
			        debounce_counter = 0;
			    }
			} else {
			    debounce_counter = 0;
			}


			break;
		case led_button:

			if(!inputSW2){
				magentaToggle();
				}

			state = init;
			break;
		case led_uart:
			break;

	}


}
void ThreadIddle(void){
	//ASM(NOP);
}
