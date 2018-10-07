/*
		STM32F3 driver for UART, source
*/


#include "uart.h"

/**
  * @brief  Init UART with specified parameters.
	*
  * @param  uartx: pointer to UARTx
	* @param  baud_rate: Uart baud rate
	* @param  wlen: UART word length, can be one of:
	*					UART_Word_8bit, UART_Word_9bit
	* @param  parity: configure parity bit, can be one of:
	*					UART_Parity_None, UART_Parity_Even, UART_Parity_Odd
	* @param  sbit: configure UART stop bit length, can be one of:
	*					UART_Stopbit_1, UART_Stopbit_2, UART_Stopbit_0_5, UART_Stopbit_1_5
  * @retval None
  */
void uart_init(USART_TypeDef *uartx, uint16_t baud_rate, UART_WordLen wlen, UART_Parity parity, UART_Stopbits sbit)
{
	
}


/**
  * @brief  Open UART to start comunication
	*
  * @param  uartx: pointer to UARTx
  * @retval None
  */
void uart_open(USART_TypeDef *uart)
{
	
}


/**
  * @brief  Close UART to start comunication
	*
  * @param  uartx: pointer to UARTx
  * @retval None
  */
void uart_close(USART_TypeDef *uart)
{
	
}


/**
  * @brief  Deinit UART hardware to default values
	*
  * @param  uartx: pointer to UARTx
  * @retval None
  */
void uart_deinit(USART_TypeDef *uart)
{
	
}
