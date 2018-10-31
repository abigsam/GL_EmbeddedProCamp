/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "gpio.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osThreadId greenLED1TaskHandle;
osThreadId greenLED2TaskHandle;
osThreadId blueLED1TaskHandle;
osThreadId blueLED2TaskHandle;
osThreadId redLED1TaskHandle;
osThreadId redLED2TaskHandle;
osThreadId orangeLED1TaskHandle;
osThreadId orangeLED2TaskHandle;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void greenLED1Task(void const * argument);
void greenLED2Task(void const * argument);
void blueLED1Task(void const * argument);
void blueLED2Task(void const * argument);
void redLED1Task(void const * argument);
void redLED2Task(void const * argument);
void orangeLED1Task(void const * argument);
void orangeLED2Task(void const * argument);

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	osThreadDef(greenLED1, greenLED1Task, osPriorityNormal, 0, 128);
	greenLED1TaskHandle = osThreadCreate(osThread(greenLED1), NULL);
	
	osThreadDef(greenLED2, greenLED2Task, osPriorityNormal, 0, 128);
	greenLED2TaskHandle = osThreadCreate(osThread(greenLED2), NULL);
	
	osThreadDef(blueLED1, blueLED1Task, osPriorityNormal, 0, 128);
	blueLED1TaskHandle = osThreadCreate(osThread(blueLED1), NULL);
	
	osThreadDef(blueLED2, blueLED2Task, osPriorityNormal, 0, 128);
	blueLED2TaskHandle = osThreadCreate(osThread(blueLED2), NULL);
	
	osThreadDef(redLED1, redLED1Task, osPriorityNormal, 0, 128);
	redLED1TaskHandle = osThreadCreate(osThread(redLED1), NULL);
	
	osThreadDef(redLED2, redLED2Task, osPriorityNormal, 0, 128);
	redLED2TaskHandle = osThreadCreate(osThread(redLED2), NULL);
	
	osThreadDef(orangeLED1, orangeLED1Task, osPriorityNormal, 0, 128);
	orangeLED1TaskHandle = osThreadCreate(osThread(orangeLED1), NULL);
	
	osThreadDef(orangeLED2, orangeLED2Task, osPriorityNormal, 0, 128);
	orangeLED2TaskHandle = osThreadCreate(osThread(orangeLED2), NULL);
	
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000u);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void greenLED1Task(void const * argument)
{
	for(;;)
	{
		LED_ON(GREEN1_LED);
		osDelay(500u);
		LED_OFF(GREEN1_LED);
		osDelay(500u);
	}
}

void greenLED2Task(void const * argument)
{
	for(;;)
	{
		LED_ON(GREEN2_LED);
		osDelay(400u);
		LED_OFF(GREEN2_LED);
		osDelay(400u);
	}
}

void blueLED1Task(void const * argument)
{
	for(;;)
	{
		LED_ON(BLUE1_LED);
		osDelay(300u);
		LED_OFF(BLUE1_LED);
		osDelay(300u);
	}
}

void blueLED2Task(void const * argument)
{
	for(;;)
	{
		LED_ON(BLUE2_LED);
		osDelay(600u);
		LED_OFF(BLUE2_LED);
		osDelay(300u);
	}
}

void redLED1Task(void const * argument)
{
	for(;;)
	{
		LED_ON(RED1_LED);
		osDelay(800u);
		LED_OFF(RED1_LED);
		osDelay(200u);
	}
}
	
	
void redLED2Task(void const * argument)
{
	for(;;)
	{
		LED_ON(RED2_LED);
		osDelay(200u);
		LED_OFF(RED2_LED);
		osDelay(800u);
	}
}

void orangeLED1Task(void const * argument)
{
	for(;;)
	{
		LED_ON(ORANGE1_LED);
		osDelay(1500u);
		LED_OFF(ORANGE1_LED);
		osDelay(1000u);
	}
}

void orangeLED2Task(void const * argument)
{
	for(;;)
	{
		LED_ON(ORANGE2_LED);
		osDelay(500u);
		LED_OFF(ORANGE2_LED);
		osDelay(3500u);
	}
}


/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
