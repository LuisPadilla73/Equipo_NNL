/*
 * THREAD_FUNCS.h
 *
 *  Created on: 8 sep. 2025
 *      Author: Gabriel
 */

#ifndef DRIVERS_THREAD_FUNCS_H_
#define DRIVERS_THREAD_FUNCS_H_
#include "thread_struct.h"
#include "GPIO.h"
#include "ADC.h"

void Thread2ms(void);
void Thread10ms(void);
void Thread5ms(void);
void ThreadIddle(void);

typedef enum{
	init = 0,
	led_button,
	led_uart,
	toggle

}GPIO;
#endif /* DRIVERS_THREAD_FUNCS_H_ */
