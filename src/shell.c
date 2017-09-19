
#include <shell.h>
#include <ushell.h>
#include <usart.h>
#include <stm32f4xx.h>


// UART configuration
extern UART_HandleTypeDef huart2;

// buffer for incoming characters
char terminal_input_buffer[2];


static inline void ushell_reboot(uint8_t argc, char* argv[])
{
    NVIC_SystemReset();
}

// microshell application setup
ushell_app_list_t apps =
{
    count: 3,
    apps:
    {
        {
            name: "help",
            help_brief: "Show this help",
        },
        {
            name: "clear",
            help_brief: "Clear screen",
        },
		{
			name: "reboot",
			help_brief: "Reboot microcontroller",
			function: &ushell_reboot
		},
    }
};

// Shell-to-UART: single character output
void terminal_output_char(uint8_t c)
{
    HAL_UART_Transmit(&huart2, &c, 1, 1000);
}

// Shell-to-UART: string output
void terminal_output_string(char* s)
{
    HAL_UART_Transmit(&huart2, (uint8_t*) s, strlen(s), 1000);
}

// UART-to-Shell: interrupt callback routine
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == UART_INSTANCE)
    {
        ushell_input_char(*terminal_input_buffer);
        HAL_UART_Receive_IT(&huart2, (uint8_t*) terminal_input_buffer, 1);
    }
}

void shell_init()
{
    USART2_Init();

	ushell_init(&apps);
	ushell_clear();
	ushell_help();
	ushell_prompt();

	// prepare to receive first char via U(S)ART
    HAL_UART_Receive_IT(&huart2, (uint8_t*) terminal_input_buffer, 1);
}
