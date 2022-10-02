/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG(int num);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  //red, green, yellow la thoi gian sang den
  //cac bien kia la counter
  int red = 5, yellow = 2, green = red - yellow;
  int green1 = green, red2 = red;
  int yellow1 = 0, red1 = 0;
  int yellow2 = 0, green2 = 0;

  //set all led off
  HAL_GPIO_WritePin(RED_LED_1_GPIO_Port, RED_LED_1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(YELLOW_LED_1_GPIO_Port, YELLOW_LED_1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GREEN_LED_1_GPIO_Port, GREEN_LED_1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(RED_LED_2_GPIO_Port, RED_LED_2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(YELLOW_LED_2_GPIO_Port, YELLOW_LED_2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GREEN_LED_2_GPIO_Port, GREEN_LED_2_Pin, GPIO_PIN_SET);

  while (1)
  {
	  //xanh 1 sang, do 2 sang
	  if(green1>0 && red2>0){
		  HAL_GPIO_WritePin(GREEN_LED_1_GPIO_Port, GREEN_LED_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(RED_LED_2_GPIO_Port, RED_LED_2_Pin, GPIO_PIN_RESET);
		  display7SEG(green1);
		  HAL_Delay(1000);
		  green1 = green1 - 1;
		  red2 = red2 - 1;
		  if(green1 <= 0){	//neu het den xanh, chuyen trang thai sang vang
			  yellow1 = yellow;
			  HAL_GPIO_WritePin(GREEN_LED_1_GPIO_Port, GREEN_LED_1_Pin, GPIO_PIN_SET);
		  }
	  }

	  //vang 1 sang, do 2 sang
	  if(yellow1>0 && red2>0){
		  HAL_GPIO_WritePin(YELLOW_LED_1_GPIO_Port, YELLOW_LED_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(RED_LED_2_GPIO_Port, RED_LED_2_Pin, GPIO_PIN_RESET);
		  display7SEG(yellow1);
		  HAL_Delay(1000);
		  yellow1 = yellow1 - 1;
		  red2 = red2 - 1;
		  if(red2 <= 0){	//het do, chuyen sang xanh2
			  green2 = green;
			  red1 = red;
			  HAL_GPIO_WritePin(YELLOW_LED_1_GPIO_Port, YELLOW_LED_1_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(RED_LED_2_GPIO_Port, RED_LED_2_Pin, GPIO_PIN_SET);
		  }
	  }

	  //do 1 sang, xanh 2 sang
	  if(red1>0 && green2>0){
		  HAL_GPIO_WritePin(RED_LED_1_GPIO_Port, RED_LED_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GREEN_LED_2_GPIO_Port, GREEN_LED_2_Pin, GPIO_PIN_RESET);
		  display7SEG(red1);
		  HAL_Delay(1000);
		  red1 = red1 - 1;
		  green2 = green2 - 1;
		  if(green2<=0){	//het xanh, chuyen sang vang2
			  HAL_GPIO_WritePin(GREEN_LED_2_GPIO_Port, GREEN_LED_2_Pin, GPIO_PIN_SET);
			  yellow2 = yellow;
		  }
	  }

	  //do 1 sang, vang 2 sang
	  if(red1>0 && yellow2>0){
		  HAL_GPIO_WritePin(RED_LED_1_GPIO_Port, RED_LED_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(YELLOW_LED_2_GPIO_Port, YELLOW_LED_2_Pin, GPIO_PIN_RESET);
		  display7SEG(red1);
		  HAL_Delay(1000);
		  red1 = red1 - 1;
		  yellow2 = yellow2 - 1;
		  if(red1<=0){	//het do, chuyen ve trang thai 1, xanh 1 sang, do 2 sang
			  HAL_GPIO_WritePin(RED_LED_1_GPIO_Port, RED_LED_1_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(YELLOW_LED_2_GPIO_Port, YELLOW_LED_2_Pin, GPIO_PIN_SET);
			  green1 = green;
			  red2 = red;
		  }
	  }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED_LED_1_Pin|YELLOW_LED_1_Pin|GREEN_LED_1_Pin|RED_LED_2_Pin
                          |YELLOW_LED_2_Pin|GREEN_LED_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, a_Pin|b_Pin|c_Pin|d_Pin
                          |e_Pin|f_Pin|g_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RED_LED_1_Pin YELLOW_LED_1_Pin GREEN_LED_1_Pin RED_LED_2_Pin
                           YELLOW_LED_2_Pin GREEN_LED_2_Pin */
  GPIO_InitStruct.Pin = RED_LED_1_Pin|YELLOW_LED_1_Pin|GREEN_LED_1_Pin|RED_LED_2_Pin
                          |YELLOW_LED_2_Pin|GREEN_LED_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : a_Pin b_Pin c_Pin d_Pin
                           e_Pin f_Pin g_Pin */
  GPIO_InitStruct.Pin = a_Pin|b_Pin|c_Pin|d_Pin
                          |e_Pin|f_Pin|g_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void display7SEG(int num)
{
	if(num==0 || num==2 || num==3 || num==5 || num==6
			|| num==7 || num==8 || num==9){
		HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_SET);

	if(num==0 || num==1 || num==2 || num==3 || num==4
		|| num==7 || num==8 || num==9){
		HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_SET);

	if(num==0 || num==1 || num==3 || num==4 || num==5 || num==6
			|| num==7 || num==8 || num==9){
		HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_SET);

	if(num==0 || num==2 || num==3 || num==5 || num==6 || num==8 ||num==9){
		HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_SET);

	if(num==0 || num==2 || num==6 || num==8){
		HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);

	if(num==0 || num==4 || num==5 || num==6 || num==8 ||num==9){
		HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_SET);

	if(num==2 || num==3 || num==4 || num==5 || num==6 || num==8 || num==9){
		HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
	}
	else HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_SET);

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
