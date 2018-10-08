

#include "stm32f303xc.h"
#include "uart.h"


/* Functiones prototypes */
void configSysclk(void);

int main(void)
{
	configSysclk(); //Switch to PLL 36 MHz
	SystemCoreClockUpdate(); //Update CMSIS SystemCoreClock variable
	
	
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

