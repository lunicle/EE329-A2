/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "keypad.h"


void keypad_displaykey(uint8_t number) {
    GPIOC->ODR &= ~(LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin); // Clear all LED pins
    // Set each LED pin according to the corresponding bit in the number
    GPIOC->ODR |= (number & 0b0001) ? LED1_Pin : 0;
    GPIOC->ODR |= (number & 0b0010) ? LED2_Pin : 0;
    GPIOC->ODR |= (number & 0b0100) ? LED3_Pin : 0;
    GPIOC->ODR |= (number & 0b1000) ? LED4_Pin : 0;
}

void delay1(uint32_t count) {
   for (uint32_t i = 0; i < count; i++) {
       __NOP(); // No operation instruction, used for software delay
   }
}

void SystemClock_Config(void);


uint8_t intbinary(int number1){
	switch (number1){
	case 1:
		return 0b0001;
	case 2:
		return 0b0010;
	case 3:
		return 0b0011;
	case 4:
		return 0b0100;
	case 5:
		return 0b0101;
	case 6:
		return 0b0110;
	case 7:
		return 0b0111;
	case 8:
		return 0b1000;
	case 9:
		return 0b1001;
	case 10:
		return 0b1010;
	case 11:
		return 0b1110;
	case 12:
		return 0b1100;

	}
}


int main(void)
{
  HAL_Init();

  SystemClock_Config();
  keypad_init();


  while (1){
//	  uint8_t key = keypad_readkey();
//	  if (key == 1){
//		  GPIOC->BSRR = LED1_Pin;
//		  delay1(1000000);
//		  GPIOC->BRR = LED1_Pin;
//	  }
//	  if (key == 2){
//		  GPIOC->BSRR = LED2_Pin;
//		  delay1(1000000);
//		  GPIOC->BRR = LED2_Pin;
//	  }
//	  if (key == 3){
//	  		  GPIOC->BSRR = LED3_Pin;
//	  		  delay1(1000000);
//	  		  GPIOC->BRR = LED3_Pin;
//	  	  }
//	  if (Keypad_IsAnyKeyPressed() == 1){
//		  GPIOC->BSRR = LED1_Pin;
//		  delay1(1000000);
//		  GPIOC->BRR = LED1_Pin;
//	  }
//	  else{
//		  GPIOC->BSRR = (LED2_Pin);
//		  delay1(50000);
//		  GPIOC->BRR = (LED2_Pin);
//		  delay1(50000);
//	  }
	  if (Keypad_IsAnyKeyPressed() == 1)
	      {
	      		uint8_t key = Keypad_WhichKeyIsPressed();
	      		keypad_displaykey(key);
	      		delay1(200000);
	      		keypad_displaykey(0);
	      	}
	    }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
