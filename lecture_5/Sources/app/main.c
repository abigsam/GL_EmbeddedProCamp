/**
 *
 *
*/



/* Includes */
#include "stm32f303xc.h"
#include "uart.h"

/* Defines */
#define UART_HANDLER		(USART1)
#define UART_SPEED			((uint32_t) 115200)
#define UART_BITS				(UART_Word_8bit)
#define UART_PARITY			(UART_Parity_None)
#define UART_STOP_BIT		(UART_Stopbit_1)

#define ECHO_DEPTH			(1u)

/* Functiones prototypes */
void configSysclk(void);

int main(void)
{
	uint8_t buffer[ECHO_DEPTH+2u] = {0u};
	
	configSysclk(); //Switch to PLL 36 MHz
	SystemCoreClockUpdate(); //Update CMSIS SystemCoreClock variable
	
	/* Init UART with defined configartion */
	uart_init(UART_HANDLER, UART_SPEED, UART_BITS, UART_PARITY, UART_STOP_BIT);
	
	uart_open(UART_HANDLER);
	
	for(;;) {
		uart_read(UART_HANDLER, buffer, ECHO_DEPTH);
		uart_write(UART_HANDLER, buffer, ECHO_DEPTH);
	}
	
	return 0;
}


/*
 * @brief		Configure SYSCLK ot maximum for
 *					HSI frequency (36 MHz)
 * @param		None
 * @retval	None
*/
void configSysclk(void)
{
	uint32_t temp = 0u;
	/* Change PLL configuration */
	RCC->CR &= ~(1 << 24); //Disable PLL
	while(RCC->CR & (1 << 25)); //Wait until PLLRDY is cleared
	//Change the desired parameter
	RCC->CFGR &= ~(0xf << 18); //Clear PLL Mul
	RCC->CFGR |= (0x7 << 18); //Set PLL Mul to 0b0111 (x9)
	RCC->CR |= (1 << 24); //Enable PLL
	/* System clock Mux to PLL */
	temp = RCC->CFGR;
	temp &= ~0x3u;
	temp |= (1 << 1); //Switch to PLL
	RCC->CFGR = temp;
}

