/*
 * PIT.h
 *
 *  Created on: 4 may. 2025
 *      Author: Gabriel
 */

#include <stdint.h>
#include "fsl_pit.h"
#include "fsl_debug_console.h"
#include "thread_struct.h"

#ifndef DRIVERS_PIT_D_H_
#define DRIVERS_PIT_D_H_

#define DEMO_PIT_BASEADDR PIT
#define DEMO_PIT_CHANNEL  kPIT_Chnl_0
#define PIT_TOGGLE_CHANNEL kPIT_Chnl_1
#define PIT_ALARM_CHANNEL kPIT_Chnl_2

#define PIT_1ms_HANDLER   PIT0_IRQHandler
#define PIT_IRQ_ID        PIT0_IRQn

#define PIT_TOGGLE_COUNT  PIT1_IRQHandler
#define PIT1_IRQ_ID        PIT1_IRQn

#define PIT_ALARM_HANDLER PIT2_IRQHandler
#define PIT2_IRQ_ID PIT2_IRQn

/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

void PIT_init();

void set_callback_PIT(void* ptr);
void set_PIT1_callback(void * ptr);
void set_PIT2_callback(void * ptr);
void get_PIT_toggle_CB(uint8_t *ptr);




#endif /* DRIVERS_PIT_H_ */
