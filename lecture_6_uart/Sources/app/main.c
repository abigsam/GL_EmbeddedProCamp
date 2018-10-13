/**
 *
 *
*/



/* Includes */
#include "stm32f303xc.h"
#include "uart.h"

/* Defines */
//USART2 RX PA3 *** TX PA2 *** CLK APB1ENR->USART2EN *** AF#7
#define UART_HANDLER		(USART1)
#define UART_SPEED			(9600u)
#define UART_BITS				(UART_Word_8bit)
#define UART_PARITY			(UART_Parity_None)
#define UART_STOP_BIT		(UART_Stopbit_1)
#define ECHO_DEPTH			(1u)

#define UART_RX_PIN  		(5)
#define UART_RX_PORT		(GPIOC)
#define UART_RX_AF_NUM	(7) //datasheet, p. 48
#define UART_TX_PIN 		(4)
#define UART_TX_PORT		(GPIOC)
#define UART_TX_AF_NUM	(7) //datasheet, p. 48

#define LED_RED_PIN			(9)
#define LED_RED_PORT		(GPIOE)

/* Macroses */
#define PIN_ON(port,pin)	do { port->ODR |= (1u << pin); } while(0);
#define PIN_OFF(port,pin)	do { port->ODR &= ~(1u << pin); } while(0);

/* Global variables */
UART_Config uconfig;

/* Functiones prototypes */
void config_sysclk(void);
void clock_control(void);
void config_led(GPIO_TypeDef *port, uint8_t pin);

int main(void)
{
	uint8_t buffer[ECHO_DEPTH+2u] = {0u};
	uint8_t temp = 'X';
	
	config_sysclk(); //Switch to PLL 36 MHz
	SystemCoreClockUpdate(); //Update CMSIS SystemCoreClock variable
	clock_control(); //Enable clocks for USART1, GPIOC, GPIOE (LEDs)
	
	/* Config LED(s) */
	config_led(LED_RED_PORT, LED_RED_PIN);
	PIN_OFF(LED_RED_PORT, LED_RED_PIN);
	
	/* Setup configartion structure */
	uconfig.baud_rate = UART_SPEED;
	uconfig.parity = UART_PARITY;
	uconfig.word_len = UART_BITS;
	uconfig.stop_bit = UART_STOP_BIT;
	/* RX pin */
	uconfig.rx_pin.port   = UART_RX_PORT;
	uconfig.rx_pin.pin    = UART_RX_PIN;
	uconfig.rx_pin.af_num = UART_RX_AF_NUM;
	/* TX pin */
	uconfig.tx_pin.port   = UART_TX_PORT;
	uconfig.tx_pin.pin    = UART_TX_PIN;
	uconfig.tx_pin.af_num = UART_TX_AF_NUM;
	/* Init UART with defined configartion */
	uart_init(&uconfig, UART_HANDLER);
	uart_open(&uconfig);
	
	for(;;) {
		uart_read(&uconfig, buffer, ECHO_DEPTH);
		PIN_ON(LED_RED_PORT, LED_RED_PIN);
		uart_write(&uconfig, buffer, ECHO_DEPTH);
		PIN_OFF(LED_RED_PORT, LED_RED_PIN);
	}
	
	return 0;
}


/*
 * @brief		Configure SYSCLK ot maximum for HSI frequency (36 MHz)
 * @param		None
 * @retval	None
*/
void config_sysclk(void)
{
	uint32_t temp = 0u;
	/* Change PLL configuration */
	RCC->CR &= ~RCC_CR_PLLON_Msk; //Disable PLL
	while(RCC->CR & RCC_CR_PLLRDY_Msk); //Wait until PLLRDY is cleared
	/* Change the desired parameter */
	RCC->CFGR &= ~(0xf << 18); //Clear PLL Mul
	RCC->CFGR |= (0x7 << 18); //Set PLL Mul to 0b0111 (x9)
	RCC->CR |= RCC_CR_PLLON_Msk; //Enable PLL
	while(!(RCC->CR & RCC_CR_PLLRDY_Msk)); //Wait until PLLRDY is set
	/* System clock Mux to PLL */
	temp = RCC->CFGR;
	temp &= ~RCC_CFGR_SW_Msk;
	temp |= RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos; //Switch to PLL
	RCC->CFGR = temp;
	while ( (RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL ); //Wait for Switch to PLL source
}


/*
 * @brief		Enable clocks for used pheripherials
 * @param		None
 * @retval	None
*/
void clock_control(void)
{
	/* Enable clock for USART1 */
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	/* Enable clock for GPIOC (USART1 RX/TX pins) */
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	/* Enable clock for GPIOE (LEDs) */
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
}


/*
 * @brief		Configure LED on board
 * @param		port: pointer to the LED port registers
 * @param   pin: LED pin number
 * @retval	None
*/
void config_led(GPIO_TypeDef *port, uint8_t pin)
{
	port->MODER &= ~(GPIO_MODER_MODER0_Msk << (pin*2)); //Clear pin mode register
	port->MODER |= 1u << (pin*2); //Set pins as output
	port->PUPDR &= ~(GPIO_PUPDR_PUPDR0_Msk << (pin*2)); //Switch off pull-up/pull-down
	port->OTYPER &= ~(1u << pin); //Configure pin output driver as push-pull
	port->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0_Msk << pin); //Set output speed as low
}


/*
 * @brief		USART1 interrupt handler
 * @param		None
 * @retval	None
*/
void USART1_IRQHandler(void)
{
	uart_interrupt_handler(&uconfig);
}
