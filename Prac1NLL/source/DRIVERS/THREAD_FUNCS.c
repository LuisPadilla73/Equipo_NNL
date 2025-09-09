/*
 * THREAD_FUNCS.c
 *
 *  Created on: 8 sep. 2025
 *      Author: Gabriel
 */

#include "THREAD_FUNCS.h"


void Thread2ms(void){
	uint8_t inputSW2= GPIO_PinRead(GPIOC, SW2);
	//inputSW3= GPIO_PinRead(GPIOA, SW3);
	static uint8_t state = 0;
	static uint8_t flag_led_button_on = 0;


	switch(state){
		case init:
			if(!inputSW2){
				state = led_button;
			}
			break;
		case led_button:
			if(!inputSW2 && !flag_led_button_on ){
				allOFF();
				magentaToggle();
				flag_led_button_on= 1;
				state = init;
			}else{
				allOFF();
				flag_led_button_on= 0;
				state = init;
			}
			break;
		case led_uart:
			break;
	}



}
void Thread10ms(void){
	static uint8_t counter = 0;
	counter++;
}
void Thread5ms(void){
	static uint8_t counter = 0;
	counter++;
}
void ThreadIddle(void){
	//ASM(NOP);
}
