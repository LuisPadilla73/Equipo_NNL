/*
 * UART.c
 *
 *  Created on: 9 sept 2025
 *      Author: luisg
 */

#include "uart.h"
#include "fsl_uart.h"
#include "board.h"

/* Arreglo global de flags */
static volatile bool uart_flags[UART_FLAG_COUNT] = {false};

/* Buffer para almacenar el comando recibido*/
static uint8_t uart_rx_buffer[64];
static uint16_t uart_rx_index = 0;

void UART_init(void) {
    uart_config_t config;

    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE; /* Usamos el baudrate definido en board.h*/
    config.enableTx = true;
    config.enableRx = true;

    UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);

    // Enable RX interrupt.
    UART_EnableInterrupts(DEMO_UART, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
    EnableIRQ(DEMO_UART_IRQn);
}

bool UART_GetFlag(uart_flags_t flag) {
    return uart_flags[flag];
}

void UART_ClearFlag(uart_flags_t flag) {
    uart_flags[flag] = false;
}

void UART_SendString(const uint8_t *string) {
	 UART_WriteBlocking(DEMO_UART, string, strlen((const char *)string));
}

/* La ISR de la UART */
void DEMO_UART_IRQHandler(void) {
    uint8_t data;

    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(DEMO_UART)) {
        data = UART_ReadByte(DEMO_UART);

        /* Si es un caracter de fin de línea (Enter)*/
        if (data == '\r' || data == '\n') {
            /* Terminar el string*/
            uart_rx_buffer[uart_rx_index] = '\0';

            /* Parsear el comando y activar la bandera correspondiente*/
            if (strcmp((char *)uart_rx_buffer, "Turn On") == 0) {
                uart_flags[UART_FLAG_TURN_ON] = true;
            } else if (strcmp((char *)uart_rx_buffer, "Turn Off") == 0) {
                uart_flags[UART_FLAG_TURN_OFF] = true;
            } else if (strncmp((char *)uart_rx_buffer, "Toggle ", 7) == 0) {
                /* Procesar "Toggle 5"*/
                uart_flags[UART_FLAG_TOGGLE] = true;
            } else if (strcmp((char *)uart_rx_buffer, "Temp") == 0) {
                uart_flags[UART_FLAG_TEMP] = true;
            } else if (strcmp((char *)uart_rx_buffer, "Help") == 0) {
                uart_flags[UART_FLAG_HELP] = true;
            }
            /* Se resetea el buffer*/
            uart_rx_index = 0;
        } else {
            /* Si no es fin de línea, guardar el caracter en el buffer*/
            if (uart_rx_index < (sizeof(uart_rx_buffer) - 1)) {
                uart_rx_buffer[uart_rx_index++] = data;
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
