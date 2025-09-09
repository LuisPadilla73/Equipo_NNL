/*
 * PIT.c
 *
 *  Created on: 4 may. 2025
 *      Author: Gabriel
 */
/*
 * PIT_D.c
 *
 *  Created on: Feb 27, 2025
 *      Author: DOOMSLAYER
 */
#include "PIT.h"
void (*ptr_func) (void) = NULL;
uint16_t (*sine_func) (void) = NULL;
void (*DISPLAY_func) (void) = NULL;

static ThreadObj* ThreadTable = NULL; // Apuntador global estático


void set_callback_PIT(void* ptr) {
    ThreadTable = (ThreadObj*)ptr;
}

void set_PIT1_callback(void * ptr) {
	DISPLAY_func = ptr;
}

void set_PIT2_callback(void * ptr) {
	sine_func = ptr;
}




uint8_t alarmflag = 0;

void PIT_1ms_HANDLER(void)
{

    /* Clear interrupt flag.*/
    PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerFlag);
    /* Added for, and affects, all PIT handlers. For CPU clock which is much larger than the IP bus clock,
     * CPU can run out of the interrupt handler before the interrupt flag being cleared, resulting in the
     * CPU's entering the handler again and again. Adding DSB can prevent the issue from happening.
     *
     *
     */

    if (ThreadTable == NULL) return;

    for(int tableCounter = 0;tableCounter<NUM_THREADS;tableCounter++){ //3 num de threads, cambiar por un enum
        	ThreadTable[tableCounter].SystemTime++;

        	if(ThreadTable[tableCounter].SystemTime >= ThreadTable[tableCounter].ThreadRate){
        		//Lo mejor es salirse de la interrupción, no podemos llamar la función aunque necesitamos lanzar el thread
        		//Cambiamos el estado para que se ejecute
        		ThreadTable[tableCounter].ThreadState = READY ;
        		ThreadTable[tableCounter].SystemTime = 0; //reiniciar el system time para que siempre cuente lo mismo


        	}
      //Agregar condicionees de prioridad, pera que se ejecute conforme la prioridad
        	// por ejemplo, ejecuta el el último que estuvo en el pit
        }



    __DSB();
}


void PIT_DISPLAY_HANDLER(void) {
    PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, PIT_DISPLAY_CHANNEL, kPIT_TimerFlag);

    static uint8_t counter = 0;

        if(counter ==  1){
        	alarmflag = 1;
        	counter = 0;
        }else{
        	alarmflag = 0;
        	counter++;
        }

        __DSB();
}

void PIT_ALARM_HANDLER(void){
	uint16_t dacValue = 0;
	PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, PIT_ALARM_CHANNEL, kPIT_TimerFlag);

}



void PIT_init() {
		pit_config_t pitConfig;
	 	 PIT_GetDefaultConfig(&pitConfig);

	    /* Init pit module */
	    PIT_Init(DEMO_PIT_BASEADDR, &pitConfig);

	    /* Set timer period for channel 0 */
	    PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, MSEC_TO_COUNT(1, PIT_SOURCE_CLOCK));

//	    PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, PIT_DISPLAY_CHANNEL, MSEC_TO_COUNT(2000, PIT_SOURCE_CLOCK));
//
//	    PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, PIT_ALARM_CHANNEL, USEC_TO_COUNT(20, PIT_SOURCE_CLOCK));

	    /* Enable timer interrupts for channel 0 */
	    PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);

//
//	    /* Enable timer interrupts for channel 1 */
//		PIT_EnableInterrupts(DEMO_PIT_BASEADDR, PIT_DISPLAY_CHANNEL, kPIT_TimerInterruptEnable);
//	    /* Enable timer interrupts for channel 2 */
//
//		PIT_EnableInterrupts(DEMO_PIT_BASEADDR, PIT_ALARM_CHANNEL, kPIT_TimerInterruptEnable);


		/* Enable at the NVIC */
	    EnableIRQ(PIT_IRQ_ID);
//	    EnableIRQ(PIT1_IRQ_ID);
//	    EnableIRQ(PIT2_IRQ_ID);



	    /* Start channel 0 */
	    PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL);


}

