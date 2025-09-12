/*
 * THREAD_CONTROL.c
 *
 *  Created on: 8 sep. 2025
 *      Author: Gabriel
 */
#include "THREAD_CONTROL.h"

ThreadObj ThreadTable[]= { //felxible, se puede tener más threads
		{Thread2ms,STANDBY,2,0} ,// función, estados, rate de 2ms
		{Thread5ms,STANDBY,5,0},
		{Thread10ms,STANDBY,10,0}
};


void program_init(){//
	GPIO_BOARD_INIT();
	UART_init();
	set_toggle_flag();
	PIT_init();
	set_callback_PIT((void*)ThreadTable);
	ADC_init();
	UART_Menu();



	while (true)
		{
			//Lanzar lo threads cuando el state está en ready
		  PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);
			for(uint8_t  tableCounter = 0 ;tableCounter<NUM_THREADS;tableCounter++){
				if(ThreadTable[tableCounter].ThreadState == READY){ // si ningun thread está en ready se debe llamar el idle

					ThreadTable[tableCounter].ThreadState = EXECUTE; //después cambiar a stanby cuando se acabe la ejecución
					ThreadTable[tableCounter].ThreadHandler(); //disparar cuando ya está en ready
					ThreadTable[tableCounter].ThreadState = STANDBY;
				}else{
					ThreadIddle();
				}

			}
			 PIT_DisableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);
		 }

}
