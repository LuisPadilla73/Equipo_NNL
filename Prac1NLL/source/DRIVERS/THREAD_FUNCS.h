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
#include "UART.h"
#include "PIT.h"

#define ADC_MAX_VALUE    4095     // 12-bit ADC (0-4095)
#define VCC              3.3     // Voltaje de referencia (asumimos 3.3V)
#define ADC_TO_VOLTAGE   (VCC / ADC_MAX_VALUE)  // Conversión de valor ADC a voltaje
#define VOLTAGE_TO_TEMP (3.3f / 50.0f)
#define DECIMAL_TO_ASCII(num) ((uint8_t)((num) + '0'))

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
