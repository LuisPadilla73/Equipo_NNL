/*
 * thread_struct.h
 *
 *  Created on: 8 sep. 2025
 *      Author: Gabriel
 */

#ifndef DRIVERS_THREAD_STRUCT_H_
#define DRIVERS_THREAD_STRUCT_H_

#include <stdio.h>
#include <stdint.h>

#define NUM_THREADS 3


typedef enum{
	STANDBY = 0,
	READY,
	EXECUTE

}ThreadState;


typedef struct{
	void(*ThreadHandler)(void);
	uint8_t ThreadState;
	uint8_t ThreadRate;
	uint8_t SystemTime;

}ThreadObj;




#endif /* DRIVERS_THREAD_STRUCT_H_ */
