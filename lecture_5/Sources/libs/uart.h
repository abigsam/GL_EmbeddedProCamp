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
	UART_WRONG_PARAM
} UART_Status;

typedef struct {
	GPIO_TypeDef *port;		/* Pointer to the port registers */
	uint8_t 			pin;		/* Pin number */
	uint8_t 			af_num;	/* Pin alternate function number (see datasheet) */
} UART_PinConfig;

typedef struct {
	uint32_t     		baud_rate; /* UART baud rate (speed) */
	UART_WordLen		word_len;  /* UART word length */
	UART_Parity  		parity;		 /* UART parity */
	UART_Stopbits 	stop_bit;  /* UART stop bit configuration */
	UART_PinConfig 	rx_pin;    /* UART RX pin configuration */
	UART_PinConfig 	tx_pin;		 /* UART TX pin configuration */
} UART_Config;

/**
  * Declaration for internal used functions
*/
static void init_gpio(UART_PinConfig *pinc);

/**
  * Declaration for global functions
*/
UART_Status uart_init(USART_TypeDef *uartx, UART_Config *config);
UART_Status uart_open(USART_TypeDef *uartx);
UART_Status uart_close(USART_TypeDef *uartx);
UART_Status uart_deinit(USART_TypeDef *uartx);
UART_Status uart_read(USART_TypeDef *uartx, uint8_t *buff, uint16_t bytes);
UART_Status uart_write(USART_TypeDef *uartx, uint8_t *buff, uint16_t bytes);


#endif //___UART_H
