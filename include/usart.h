
#ifndef __usart_H
#define __usart_H

// for USART2_IRQn
#include <stm32f4xx.h>

/*
 * Nucleo's ST-Link's UART Interface
 */
#define UART_INSTANCE       USART2
#define UART_GPIO_PORT      GPIOA
#define UART_RX_PIN         GPIO_PIN_3
#define UART_TX_PIN         GPIO_PIN_2
#define UART_GPIO_AF        GPIO_AF7_USART2
#define UART_IRQ            USART2_IRQn


/**
 * Initialize USART2 as UART interface to PC via ST-Link debugger
 */
void USART2_Init(void);

/*
 * Low-level i/o functions for newlib, e.g. for printf
 */

/**
 * Read a char from input; implemented as stub,
 * because all input goes to ushell
 */
int _read(int file, char *ptr, int len);

/**
 * Write string to PC via UART
 *
 * @param file: File/pipe to write to; here disregarded
 * @param ptr:  Pointer to buffer to write to UART
 * @param len:  Length of write buffer in bytes
 */
int _write(int file, char *ptr, int len);

#endif
