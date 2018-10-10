/*
		STM32F3 driver for UART, source
*/


#include "uart.h"

/* Macroses */
#define ASSERT_UART_PTR(ptr)		do { if (0 == ptr) return UART_WRONG_PARAM; } while(0);
#define ASSERT_BAUD_RATE(spd)		do { if (0 == spd) return UART_WRONG_PARAM; } while(0);
#define ASSERT_WORD_BITS(wl)		do { if (wl != UART_Word_8bit) return UART_WRONG_PARAM; } while(0);
#define ASSERT_PARITY(prt)			do { if ( prt != UART_Parity_None && \
																				  prt != UART_Parity_Even && \
																				  prt != UART_Parity_Odd ) return UART_WRONG_PARAM; } while(0);
#define ASSERT_STOP_BITS(sb)		do { if ( sb != UART_Stopbit_1 && \
																					sb != UART_Stopbit_0_5 && \
																					sb != UART_Stopbit_2 && \
																					sb != UART_Stopbit_1_5 ) return UART_WRONG_PARAM; } while(0);


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
  * @retval UART_OK if all OK
  */
UART_Status uart_init(USART_TypeDef *uartx, uint32_t baud_rate, UART_WordLen wlen, UART_Parity parity, UART_Stopbits sbit)
{
	/* Check input parameters */
	ASSERT_UART_PTR(uartx);
	ASSERT_BAUD_RATE(baud_rate);
	ASSERT_WORD_BITS(wlen);
	ASSERT_PARITY(parity);
	/* Configure UARTx */
	uart_close(uartx); //Disable UART
	/* Configure baud rate (oversampling 16 by default)
	 * baud_rate = Fck / baud_rate (Reference Manual p. 901)
	 * SystemCoreClock -- from system_stm32f3xx.h
	*/
	uartx->BRR = (uint16_t) (SystemCoreClock / baud_rate);
	/* Configure word length */
	uartx->CR1 &= ~USART_CR1_M0_Msk;
	uartx->CR1 |= (uint32_t)wlen << USART_CR1_M0_Pos;
	/* Configure parity */
	uartx->CR1 &= ~(USART_CR1_PS_Msk | USART_CR1_PCE_Msk);
	uartx->CR1 |= (uint32_t)parity << USART_CR1_PS_Pos;
	/* Configure stop bits */
	uartx->CR2 &= ~USART_CR2_STOP;
	uartx->CR2 |= (uint32_t)sbit << USART_CR2_STOP_Pos;
	return UART_OK;
}


/**
  * @brief  Open UART to start comunication
	*
  * @param  uartx: pointer to UARTx
  * @retval UART_OK if all OK
  */
UART_Status uart_open(USART_TypeDef *uartx)
{
	/* Check input parameters */
	ASSERT_UART_PTR(uartx);
	
	uartx->CR1 |= USART_CR1_UE;
	return UART_OK;
}


/**
  * @brief  Close UART to start comunication
	*
  * @param  uartx: pointer to UARTx
  * @retval UART_OK if all OK
  */
UART_Status uart_close(USART_TypeDef *uartx)
{
	/* Check input parameters */
	ASSERT_UART_PTR(uartx);
	
	uartx->CR1 &= ~USART_CR1_UE;
	return UART_OK;
}


/**
  * @brief  Deinit UART hardware to default values
	*
  * @param  uartx: pointer to UARTx
  * @retval UART_OK if all OK
  */
UART_Status uart_deinit(USART_TypeDef *uartx)
{
	/* Check input parameters */
	ASSERT_UART_PTR(uartx);
	
	uart_close(uartx); //Disable UART
	uartx->BRR = 0u;
	uartx->CR1 = 0u;
	uartx->CR2 = 0u;
	return UART_OK;
}


/**
  * @brief  Receive specified number of bits via UARTx
	*
  * @param  uartx: pointer to UARTx
	* @param	buff: pointer to buffer
	* @param  bytes: number of bytes to read
  * @retval UART_OK if all OK
  */
UART_Status uart_read(USART_TypeDef *uartx, uint8_t *buff, uint16_t bytes)
{
	
	/* Check input parameters */
	ASSERT_UART_PTR(uartx);
	
	return UART_OK;
}


/**
  * @brief  Send specified number of bits via UARTx
	*
  * @param  uartx: pointer to UARTx
	* @param	buff: pointer to buffer
	* @param  bytes: number of bytes to read
  * @retval UART_OK if all OK
  */
UART_Status uart_write(USART_TypeDef *uartx, uint8_t *buff, uint16_t bytes)
{
	
	/* Check input parameters */
	ASSERT_UART_PTR(uartx);
	
	return UART_OK;
}

