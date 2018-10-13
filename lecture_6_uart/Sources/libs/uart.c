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
  * @brief  Init UART GPIOs
	*
  * @param  pinc: pointer to UART pin configuration (port, pin number, AF number)
  * @retval None
*/
static void init_gpio(UART_PinConfig *pinc)
{
	uint32_t tmp = 0u;
	pinc->port->MODER &= ~(GPIO_MODER_MODER0_Msk << (pinc->pin*2)); //Clear pin mode register
	pinc->port->MODER |= 2u << (pinc->pin*2); //Set pins as Alternate Function
	pinc->port->PUPDR &= ~(GPIO_PUPDR_PUPDR0_Msk << (pinc->pin*2)); //Switch off pull-up/pull-down
	pinc->port->OTYPER &= ~(1u << (pinc->pin)); //Configure pin output driver as push-pull
	tmp = pinc->pin / 8; //Find out AFR register number
	pinc->port->AFR[tmp] &= ~(GPIO_AFRL_AFRL0_Msk << (pinc->pin*4)); //Clear alternate function register
	pinc->port->AFR[tmp] |= pinc->af_num << (pinc->pin*4); //Write alternate function number
}


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
UART_Status uart_init(USART_TypeDef *uartx, UART_Config *config)// uint32_t baud_rate, UART_WordLen wlen, UART_Parity parity, UART_Stopbits sbit)
{
	/* Check input parameters */
	ASSERT_UART_PTR(uartx);
	ASSERT_BAUD_RATE(config->baud_rate);
	ASSERT_WORD_BITS(config->word_len);
	ASSERT_PARITY(config->parity);
	/* Configure UARTx */
	uart_close(uartx); //Disable UART
	/* Configure baud rate (oversampling 16 by default)
	 * baud_rate = Fck / baud_rate (Reference Manual p. 901)
	 * SystemCoreClock -- from system_stm32f3xx.h
	*/
	uartx->BRR = (uint16_t) (SystemCoreClock / config->baud_rate);
	/* Configure word length */
	uartx->CR1 &= ~USART_CR1_M0_Msk;
	uartx->CR1 |= (uint32_t)(config->word_len) << USART_CR1_M0_Pos;
	/* Configure parity */
	uartx->CR1 &= ~(USART_CR1_PS_Msk | USART_CR1_PCE_Msk);
	uartx->CR1 |= (uint32_t)(config->parity) << USART_CR1_PS_Pos;
	/* Configure stop bits */
	uartx->CR2 &= ~USART_CR2_STOP;
	uartx->CR2 |= (uint32_t)(config->stop_bit) << USART_CR2_STOP_Pos;
	init_gpio(&(config->rx_pin)); //Configure RX pin
	init_gpio(&(config->tx_pin)); //Configure TX pin
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
	uartx->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
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
	uartx->CR1 &= ~(USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
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
	uint16_t byte_cnt;
	/* Check input parameters */
	ASSERT_UART_PTR(uartx);
	if ((0 == buff) || (0 == bytes)) {
		return UART_WRONG_PARAM;
	}
	/* Wait for RX not busy */
	while(uartx->ISR & USART_ISR_BUSY) {}
	/* Read specified number of bytes */
	for (byte_cnt = 0u; byte_cnt < bytes; byte_cnt++) {
		while(!(uartx->ISR & USART_ISR_RXNE)) {} //Wait for read data register not empty
		*(buff + byte_cnt) = uartx->RDR;
	}
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
	uint16_t byte_cnt;
	/* Check input parameters */
	ASSERT_UART_PTR(uartx);
	if ((0 == buff) || (0 == bytes)) {
		return UART_WRONG_PARAM;
	}
	/* Wait for transmitter is ready */
	while (!(uartx->ISR & USART_ISR_TC)) {}
	/* Write specified number of bytes */
	for (byte_cnt = 0u; byte_cnt < bytes; byte_cnt++) {
		while(!(uartx->ISR & USART_ISR_TXE)) {} //Transmit data register empty
		uartx->TDR = *(buff + byte_cnt);
	}
	return UART_OK;
}


/**
  * @brief  UARTx interrupt handler
	*
  * @param  uartx: pointer to UARTx
  * @retval None
*/
void uart_interrupt_handler(USART_TypeDef *uartx)
{
	
}

