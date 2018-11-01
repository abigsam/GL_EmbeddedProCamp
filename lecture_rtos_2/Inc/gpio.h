/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
//LEDs common macroses
#define LED_ON(port,pin)			do {HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);} while(0);
#define LED_OFF(port,pin)			do {HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);} while(0);
#define LED_TOGGLE(port,pin)	do {HAL_GPIO_TogglePin(port, pin);} while(0);
//Macroses for each LED
#define BLUE1_LED_ON()				LED_ON(LD4_GPIO_Port, LD4_Pin)
#define BLUE1_LED_OFF()				LED_OFF(LD4_GPIO_Port, LD4_Pin)
#define RED1_LED_ON()					LED_ON(LD3_GPIO_Port, LD3_Pin)
#define RED1_LED_OFF()				LED_OFF(LD3_GPIO_Port, LD3_Pin)
#define ORANGE1_LED_ON()			LED_ON(LD5_GPIO_Port, LD5_Pin)
#define ORANGE1_LED_OFF()			LED_OFF(LD5_GPIO_Port, LD5_Pin)
#define GREEN1_LED_ON()				LED_ON(LD7_GPIO_Port, LD7_Pin)
#define GREEN1_LED_OFF()			LED_OFF(LD7_GPIO_Port, LD7_Pin)
#define BLUE2_LED_ON()				LED_ON(LD9_GPIO_Port, LD9_Pin)
#define BLUE2_LED_OFF()				LED_OFF(LD9_GPIO_Port, LD9_Pin)
#define RED2_LED_ON()					LED_ON(LD10_GPIO_Port, LD10_Pin)
#define RED2_LED_OFF()				LED_OFF(LD10_GPIO_Port, LD10_Pin)
#define ORANGE2_LED_ON()			LED_ON(LD8_GPIO_Port, LD8_Pin)
#define ORANGE2_LED_OFF()			LED_OFF(LD8_GPIO_Port, LD8_Pin)
#define GREEN2_LED_ON()				LED_ON(LD6_GPIO_Port, LD6_Pin)
#define GREEN2_LED_OFF()			LED_OFF(LD6_GPIO_Port, LD6_Pin)

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void all_leds_off(void);
void all_leds_on(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
