/*
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    Prac1NLL.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "THREAD_CONTROL.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
#include "GPIO.h"
#include "UART.h"
#include "PIT.h"
#include "THREAD_CONTROL.h"
#include "THREAD_FUNCS.h"
#include "thread_struct.h"
#include "ADC.h"

// Tabla de threads definida en THREAD_CONTROL.c
extern ThreadObj ThreadTable[];

void program_init(void) {
    // Inicializa pines, relojes y LEDs
    GPIO_BOARD_INIT();

    // Inicializa UART (configuración + interrupciones)
    UART_init();

    // Configura bandera para toggle por PIT
    set_toggle_flag();

    // Inicializa el timer PIT
    PIT_init();

    // Asocia la tabla de threads al PIT
    set_callback_PIT((void*)ThreadTable);

    // Muestra el menú de comandos por UART
    UART_Menu();

    // Bucle principal del sistema
    while (true) {
        // Habilita interrupciones del PIT
        PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);

        // Recorre los threads
        for (uint8_t tableCounter = 0; tableCounter < NUM_THREADS; tableCounter++) {
            if (ThreadTable[tableCounter].ThreadState == READY) {
                // Ejecuta el thread si está listo
                ThreadTable[tableCounter].ThreadState = EXECUTE;
                ThreadTable[tableCounter].ThreadHandler();
                ThreadTable[tableCounter].ThreadState = STANDBY;
            }  {
                // Si ningún thread está listo, ejecuta el idle
                ThreadIddle();
            }
        }

        // Deshabilita interrupciones del PIT (evita conflictos durante ejecución)
        PIT_DisableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);
    }
}

