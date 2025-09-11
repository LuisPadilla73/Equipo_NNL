/*
 * UART.h
 *
 *  Created on: 11 sep. 2025
 *      Author: Gabriel
 */

/*
 * UART.h
 *
 *  Created on: 9 sept 2025
 *      Author: luisg
 */

#ifndef DRIVERS_UART_H_
#define DRIVERS_UART_H_

#include "fsl_uart.h"

/* UART instance and clock */
#define DEMO_UART            UART0
#define DEMO_UART_CLKSRC     UART0_CLK_SRC
#define DEMO_UART_CLK_FREQ   CLOCK_GetFreq(UART0_CLK_SRC)
#define DEMO_UART_IRQn       UART0_RX_TX_IRQn
#define DEMO_UART_IRQHandler UART0_RX_TX_IRQHandler

// Enum para las banderas de comandos
typedef enum {
    UART_FLAG_TURN_ON = 0,
    UART_FLAG_TURN_OFF,
    UART_FLAG_TOGGLE,
    UART_FLAG_TEMP,
    UART_FLAG_HELP,
    UART_FLAG_COUNT
} uart_flags_t;

// Inicializa la UART
void UART_init(void);
// Obtiene estado de una bandera para que el thread de 2ms la lea
bool UART_GetFlag(uart_flags_t flag);
// Limpia una bandera para que el thread de 2ms la apague después de procesar
void UART_ClearFlag(uart_flags_t flag);
// Enviar una cadena por UART para enviar respuestas
void UART_SendString(const uint8_t *string);
// Para enviar temperatura
void UART_SendTemperature(float temperature)

uint8_t UART_GetTime() ;
#endif /* DRIVERS_UART_H_ */
