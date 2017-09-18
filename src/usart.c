
#include "usart.h"

// for return code EBADF
#include "errno.h"

#ifdef STM32CUBE
#include <stm32f4xx.h>
#endif


/**
 * A pointer to a list of environment variables and their values.
 * For a minimal environment, this empty list is adequate:
 */
char *__env[1] = { 0 };
char **environ = __env;


/**
 * This handle is used elsewhere for receiving/transmitting
 */
UART_HandleTypeDef huart2;


void USART2_Init(void)
{
	// enable GPIO clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

	// configure GPIO pins as USART pins
	GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = UART_TX_PIN | UART_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = UART_GPIO_AF;
    HAL_GPIO_Init(UART_GPIO_PORT, &GPIO_InitStruct);

    // enable USART clock
    __HAL_RCC_USART2_CLK_ENABLE();

    // initialize USART2 as UART interface
    huart2.Instance = UART_INSTANCE;
    huart2.Init.BaudRate = 460800;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
#ifdef STM32F3XX
    huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
#endif
    HAL_UART_Init(&huart2);

    // enable interrupt
    HAL_NVIC_SetPriority(UART_IRQ, 2, 0);
    HAL_NVIC_EnableIRQ(UART_IRQ);
}


int _read(int file, char *ptr, int len)
{
    // Reading from stdin is not supported on this system,
    // because all input is received by ushell.
    return EBADF;
}


int _write(int file, char *ptr, int len)
{
    extern void terminal_output_char(uint8_t c);
    for (uint32_t i=0; i<len; i++)
        terminal_output_char(*ptr++);
    return len;
}
