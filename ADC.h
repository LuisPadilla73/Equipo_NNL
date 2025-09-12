/*
 * ADC.h
 *
 *  Created on: 4 may. 2025
 *      Author: Gabriel
 */

#ifndef DRIVERS_ADC_H_
#define DRIVERS_ADC_H_


#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_adc16.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ADC16_BASE          ADC1
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL  14U

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*ADC initialization for channel 14*/
int ADC_init(void);
/*Read de actual ADC value*/
uint16_t ADC_Read(void);

#endif /* ADC_H_ */
