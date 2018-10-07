/*
		STM32F3 driver for UART, header
*/

#ifndef ___UART_H
#define ___UART_H


#include "stm32f303xc.h"

typedef enum {
	UART_Word_8bit = 0,
	UART_Word_9bit
} UART_WordLen;

typedef enum {
	UART_Parity_None = 0,
	UART_Parity_Even,
	UART_Parity_Odd
} UART_Parity;

typedef enum {
	UART_Stopbit_1 = 0,
	UART_Stopbit_2,
	UART_Stopbit_0_5,
	UART_Stopbit_1_5
} UART_Stopbits;

void uart_init(USART_TypeDef *uartx, uint16_t baud_rate, UART_WordLen wlen, UART_Parity parity, UART_Stopbits sbit);
void uart_open(USART_TypeDef *uart);
void uart_close(USART_TypeDef *uart);
void uart_deinit(USART_TypeDef *uart);



#endif //___UART_H
