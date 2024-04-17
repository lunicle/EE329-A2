/*
 * keypad.c
 *
 *  Created on: Apr 14, 2024
 *      Author: School
 */
// keypad.c
#include "keypad.h"
#include "main.h"
#define SETTLE 100


void keypad_init(void) {
	// configure GPIO pins PC0, PC1, PC2, PC3 for:
	// output mode, push-pull, no pull up or pull down, high speed
	//ROW PORTS
	RCC->AHB2ENR   |=  (RCC_AHB2ENR_GPIOCEN);
   GPIOC->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2
	| GPIO_MODER_MODER3);
   GPIOC->MODER |= (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0
	| GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0);
   GPIOC->OTYPER  &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 | GPIO_OTYPER_OT2
	| GPIO_OTYPER_OT3);
   GPIOC->PUPDR   &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 | GPIO_PUPDR_PUPD2
	| GPIO_PUPDR_PUPD3);
   GPIOC->OSPEEDR |=  ((3 << GPIO_OSPEEDR_OSPEED0_Pos)
	|(3 << GPIO_OSPEEDR_OSPEED1_Pos) |(3 << GPIO_OSPEEDR_OSPEED2_Pos)
	|(3 << GPIO_OSPEEDR_OSPEED3_Pos));

	// configure GPIO pins PC4, PC5, PC6 for Input, with pull down
	//COLUMN PORTS
   GPIOC->MODER &= ~(GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6);
   GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD4 | GPIO_PUPDR_PUPD5 | GPIO_PUPDR_PUPD6);

   // configure GPIO pins PC7, PC8, PC9, PC10 for:
   	// output mode, push-pull, no pull up or pull down, high speed

   GPIOC->MODER &= ~(GPIO_MODER_MODER7 | GPIO_MODER_MODER8 | GPIO_MODER_MODER9
   	| GPIO_MODER_MODER10);
      GPIOC->MODER |= (GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0
   	| GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0);
      GPIOC->OTYPER  &= ~(GPIO_OTYPER_OT7 | GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9
   	| GPIO_OTYPER_OT10);
      GPIOC->PUPDR   &= ~(GPIO_PUPDR_PUPD7 | GPIO_PUPDR_PUPD8 | GPIO_PUPDR_PUPD9
   	| GPIO_PUPDR_PUPD10);
      GPIOC->OSPEEDR |=  ((3 << GPIO_OSPEEDR_OSPEED7_Pos)
   	|(3 << GPIO_OSPEEDR_OSPEED8_Pos) |(3 << GPIO_OSPEEDR_OSPEED9_Pos)
   	|(3 << GPIO_OSPEEDR_OSPEED10_Pos));
}


int keypad_anykey(void){
	HAL_GPIO_WritePin (ROW_PORT,Row_1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_4_Pin,GPIO_PIN_SET);
	for ( uint16_t idx=0; idx<SETTLE; idx++ ){  	// let it settle
	      ;
	  if (HAL_GPIO_ReadPin(COL_PORT,Col_1_Pin | Col_2_Pin | Col_3_Pin)){
		   return '1';
	  }
	  else{
		  return '0';
	  }
	}
}


int keypad_readkey(void){

	HAL_GPIO_WritePin (ROW_PORT,Row_1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (ROW_PORT,Row_2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_4_Pin,GPIO_PIN_SET);

	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_1_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_1_Pin)){
			return '1';
		}
	}
	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_2_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_2_Pin)){
			return '2';
		}
	}
	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_3_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_3_Pin)){
			return '3';
		}
	}

	HAL_GPIO_WritePin (ROW_PORT,Row_1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (ROW_PORT,Row_3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_4_Pin,GPIO_PIN_SET);
	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_1_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_1_Pin)){
			return '4';
		}
	}
	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_2_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_2_Pin)){
			return '5';
		}
	}
	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_3_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_3_Pin)){
			return '6';
		}
	}

	HAL_GPIO_WritePin (ROW_PORT,Row_1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (ROW_PORT,Row_4_Pin,GPIO_PIN_SET);

	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_1_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_1_Pin)){
			return '7';
		}
	}
	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_2_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_2_Pin)){
			return '8';
		}
	}
	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_3_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_3_Pin)){
			return '9';
		}

	}

	HAL_GPIO_WritePin (ROW_PORT,Row_1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (ROW_PORT,Row_4_Pin,GPIO_PIN_RESET);

	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_1_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_1_Pin)){
			return 10;
		}
	}
	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_2_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_2_Pin)){
			return 0;
		}
	}
	if (!(HAL_GPIO_ReadPin(COL_PORT,Col_3_Pin))){
		while (!HAL_GPIO_ReadPin(COL_PORT,Col_3_Pin)){
			return 11;
		}

	}

}
//readkey end bracket
