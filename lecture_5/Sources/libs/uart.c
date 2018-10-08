/*
		STM32F3 driver for UART, source
*/


#include "uart.h"

/**
  * @brief  Init UART with specified parameters.
	*
  * @param  uartx: pointer to UARTx
	* @param  baud_rate: Uart baud rate, calculated based on SystemCoreClock
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
	uint32_t temp32 = 0u;
	uart_close(uartx); //Disable UART
	/* Configure baud rate (oversampling 16 by default)
	 * baud_rate = Fck / baud_rate
	 * SystemCoreClock -- from system_stm32f3xx.h
	*/
	uartx->BRR = SystemCoreClock / baud_rate;
	/* Configure word length */
	uartx->CR1 &= ~USART_CR1_M0_Msk;
	uartx->CR1 |= (uint32_t)wlen << USART_CR1_M0_Pos;
	/* Configure parity */
	uartx->CR1 &= ~(USART_CR1_PS_Msk | USART_CR1_PCE_Msk);
	uartx->CR1 |= (uint32_t)parity << USART_CR1_PS_Pos;
	/* Configure stop bits */
	uartx->CR2 &= ~USART_CR2_STOP;
	uartx->CR2 |= (uint32_t)sbit << USART_CR2_STOP_Pos;
}


/**
  * @brief  Open UART to start comunication
	*
  * @param  uartx: pointer to UARTx
  * @retval None
  */
void uart_open(USART_TypeDef *uartx)
{
	uartx->CR1 |= USART_CR1_UE;
}


/**
  * @brief  Close UART to start comunication
	*
  * @param  uartx: pointer to UARTx
  * @retval None
  */
void uart_close(USART_TypeDef *uartx)
{
	uartx->CR1 &= ~USART_CR1_UE;
}


/**
  * @brief  Deinit UART hardware to default values
	*
  * @param  uartx: pointer to UARTx
  * @retval None
  */
void uart_deinit(USART_TypeDef *uartx)
{
	uart_close(uartx); //Disable UART
	uartx->BRR = 0u;
	uartx->CR1 = 0u;
	uartx->CR2 = 0u;
}
