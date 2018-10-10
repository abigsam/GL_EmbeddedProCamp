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

#define UART_RX_GPIO		(5)
#define UART_RX_PORT		(GPIOC)
#define UART_RX_AF_NUM	(7) //datasheet, p. 48
#define UART_TX_GPIO		(4)
#define UART_TX_PORT		(GPIOC)
#define UART_TX_AF_NUM	(7) //datasheet, p. 48

/* Functiones prototypes */
void configSysclk(void);

int main(void)
{
	uint8_t buffer[ECHO_DEPTH+2u] = {0u};
	UART_Config uconfig;
	
	configSysclk(); //Switch to PLL 36 MHz
	SystemCoreClockUpdate(); //Update CMSIS SystemCoreClock variable
	
	/* Init UART with defined configartion */
	uconfig.baud_rate = UART_SPEED;
	uconfig.parity = UART_PARITY;
	uconfig.word_len = UART_BITS;
	uconfig.stop_bit = UART_STOP_BIT;
	uconfig.rx_pin.port = UART_RX_PORT;
	uconfig.rx_pin.pin  = UART_RX_GPIO;
	uconfig.rx_pin.pin  = UART_RX_GPIO;
	uconfig.tx_pin.port = UART_TX_PORT;
	uconfig.tx_pin.pin  = UART_TX_GPIO;
	uconfig.tx_pin.pin  = UART_TX_GPIO;
	//
	uart_init(UART_HANDLER, &uconfig);
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

