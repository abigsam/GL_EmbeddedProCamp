/*
		STM32F3 driver for UART, header
*/

#ifndef ___UART_H
#define ___UART_H


#include "stm32f303xc.h"

typedef enum {
	UART_Word_8bit = (0x00)//,
	//UART_Word_9bit = (0x01)  //Temporary not implemented
	//UART_Word_7bit = (0x10)  //Temporary not implemented
} UART_WordLen;

typedef enum {
	UART_Parity_None = (0x00),
	UART_Parity_Even = (0x02),
	UART_Parity_Odd  = (0x03)
} UART_Parity;

typedef enum {
	UART_Stopbit_1   = (0x00),
	UART_Stopbit_0_5 = (0x01),
	UART_Stopbit_2   = (0x02),
	UART_Stopbit_1_5 = (0x03),
} UART_Stopbits;

typedef enum {
	UART_OK = 0,
	UART_WRONG_PARAM,
	UART_BUSY,
	UART_OVERRUN
} UART_Status;

typedef struct {
	GPIO_TypeDef *port;		/* Pointer to the port registers */
	uint8_t 			pin;		/* Pin number */
	uint8_t 			af_num;	/* Pin alternate function number (see datasheet) */
} UART_PinConfig;

typedef struct {
	USART_TypeDef   *uart;     /* UART instance */
	uint32_t     		baud_rate; /* UART baud rate (speed) */
	UART_WordLen		word_len;  /* UART word length */
	UART_Parity  		parity;		 /* UART parity */
	UART_Stopbits 	stop_bit;  /* UART stop bit configuration */
	UART_PinConfig 	rx_pin;    /* UART RX pin configuration */
	UART_PinConfig 	tx_pin;		 /* UART TX pin configuration */
	uint8_t         *tx_ptr;   /* UART TX buffer pointer */
	uint8_t         *rx_ptr;   /* UART RX buffer pointer */
	uint16_t        tx_size;   /* UART TX buffer size */
	uint16_t        rx_size;   /* UART RX buffer size */
	uint8_t					rx_busy;	 /* If UART reciever is busy it equal to 1 */
	uint8_t					tx_busy;	 /* If UART transmitter is busy it equal to 1 */
	uint8_t					rx_overrun; /* If UART receiver overrun error ocurred */
} UART_Config;

/**
  * Declaration for internal used functions
*/
static void init_gpio(UART_PinConfig *pinc);
static UART_Status init_uart(UART_Config *config, USART_TypeDef *uartx);

/**
  * Declaration for global functions (common)
*/
UART_Status uart_init(UART_Config *config, USART_TypeDef *uartx);
UART_Status uart_open(UART_Config *config);
UART_Status uart_close(UART_Config *config);
UART_Status uart_deinit(UART_Config *config);

/**
  * Declaration for polling functions
*/
UART_Status uart_read(UART_Config *config, uint8_t *buff, uint16_t bytes);
UART_Status uart_write(UART_Config *config, uint8_t *buff, uint16_t bytes);

/**
  * Declaration for interrupt functions
*/
UART_Status uart_interrupt_read(UART_Config *config, uint8_t *buff, uint16_t bytes);
UART_Status uart_interrupt_write(UART_Config *config, uint8_t *buff, uint16_t bytes);
void uart_interrupt_handler(UART_Config *config); //Insert this function to the appropriate IRQ handler

#endif //___UART_H
