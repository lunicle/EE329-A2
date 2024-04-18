/*
 * keypad.c
 *
 *  Created on: Apr 14, 2024
 *      Author: School
 */
// keypad.c
#include "keypad.h"
#include "main.h"
#define SETTLE 10
#define BIT0 0x1

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
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   // Configure the pins as input
   GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6; // Assuming pins 0, 1, and 2
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Pull = GPIO_PULLDOWN; // You can set the pull-up/pull-down as needed
   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


   // configure GPIO pins PC7, PC8, PC9, PC10 for:
   	// output mode, push-pull, no pull up or pull down, high speed

   GPIOC->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9 | GPIO_MODER_MODER10
   	| GPIO_MODER_MODER11);
      GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0
   	| GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0);
      GPIOC->OTYPER  &= ~(GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9 | GPIO_OTYPER_OT10
   	| GPIO_OTYPER_OT11);
      GPIOC->PUPDR   &= ~(GPIO_PUPDR_PUPD8 | GPIO_PUPDR_PUPD9 | GPIO_PUPDR_PUPD10
   	| GPIO_PUPDR_PUPD11);
      GPIOC->OSPEEDR |=  ((3 << GPIO_OSPEEDR_OSPEED8_Pos)
   	|(3 << GPIO_OSPEEDR_OSPEED9_Pos) |(3 << GPIO_OSPEEDR_OSPEED10_Pos)
   	|(3 << GPIO_OSPEEDR_OSPEED11_Pos));
}

int Keypad_IsAnyKeyPressed(void) {
// drive all COLUMNS HI; see if any ROWS are HI
// return true if a key is pressed, false if not
// currently no debounce here - just looking for a key twitch
   ROW_PORT->BSRR = ROW_PINS;         	      // set all columns HI
   for ( uint16_t idx=0; idx<SETTLE; idx++ )   	// let it settle
      ;
   if ((COL_PORT->IDR & COL_PINS) != 0 )        // got a keypress!
      return 1;
   else
      return 0;                          // nope.
}

int keypad_anykey(void){
	ROW_PORT->BSRR = (Row_1_Pin | Row_2_Pin | Row_3_Pin | Row_4_Pin);
	for ( uint16_t idx=0; idx<SETTLE; idx++ ){  	// let it settle
	      ;
	  if ((ROW_PORT->IDR & ROW_PINS) != 0 ){
		   return '1';
	  }
	  else{
		  return '0';
	  }
	return '0';
	}
}

//int keypad_testkey(void){
//	ROW_PORT->BSRR = Row_1_Pin;
//	if (~(GPIOB->IDR & Col_1_Pin) == 0) {
//		while (~(GPIOB->IDR & Col_1_Pin) == 0) {
//			return 1;
//		}
//	}
//	// Check COL2
//	if (~(GPIOB->IDR & Col_2_Pin) == 0) {
//		while (~(GPIOB->IDR & Col_2_Pin) == 0) {
//			return 2;
//		}
//	}
//	// Check COL3
//	if (~(GPIOB->IDR & Col_3_Pin) == 0) {
//		while (~(GPIOB->IDR & Col_3_Pin) == 0) {
//			return 3;
//		}
//	}
//}

//uint8_t keypad_readkey(void) {
//    // Reset ROW1 and set other rows
//    ROW_PORT->BRR = Row_1_Pin;
//    ROW_PORT->BSRR = (Row_2_Pin | Row_3_Pin | Row_4_Pin);
//
//    // Check COL1
//    if ((GPIOC->IDR & Col_1_Pin) == 0) {
//        while ((GPIOC->IDR & Col_1_Pin) == 0) {
//            return 0b0001; // Binary representation of '1'
//        }
//    }
//    // Check COL2
//    if ((GPIOC->IDR & Col_2_Pin) == 0) {
//        while ((GPIOC->IDR & Col_2_Pin) == 0) {
//            return 0b0010; // Binary representation of '2'
//        }
//    }
//    // Check COL3
//    if ((GPIOC->IDR & Col_3_Pin) == 0) {
//        while ((GPIOC->IDR & Col_3_Pin) == 0) {
//            return 0b0011; // Binary representation of '3'
//        }
//    }
//
//    // Reset ROW2 and set other rows
//    ROW_PORT->BRR = Row_2_Pin;
//    ROW_PORT->BSRR = (Row_1_Pin | Row_3_Pin | Row_4_Pin);
//
//    // Check COL1
//    if ((GPIOC->IDR & Col_1_Pin) == 0) {
//        while ((GPIOC->IDR & Col_1_Pin) == 0) {
//            return 0b0100; // Binary representation of '4'
//        }
//    }
//    // Check COL2
//    if ((GPIOC->IDR & Col_2_Pin) == 0) {
//        while ((GPIOC->IDR & Col_2_Pin) == 0) {
//            return 0b0101; // Binary representation of '5'
//        }
//    }
//    // Check COL3
//    if ((GPIOC->IDR & Col_3_Pin) == 0) {
//        while ((GPIOC->IDR & Col_3_Pin) == 0) {
//            return 0b0110; // Binary representation of '6'
//        }
//    }
//
//    // Reset ROW3 and set other rows
//    ROW_PORT->BRR = Row_3_Pin;
//    ROW_PORT->BSRR = (Row_1_Pin | Row_2_Pin | Row_4_Pin);
//
//    // Check COL1
//    if ((GPIOC->IDR & Col_1_Pin) == 0) {
//        while ((GPIOC->IDR & Col_1_Pin) == 0) {
//            return 0b0111; // Binary representation of '7'
//        }
//    }
//    // Check COL2
//    if ((GPIOC->IDR & Col_2_Pin) == 0) {
//        while ((GPIOC->IDR & Col_2_Pin) == 0) {
//            return 0b1000; // Binary representation of '8'
//        }
//    }
//    // Check COL3
//    if ((GPIOC->IDR & Col_3_Pin) == 0) {
//        while ((GPIOC->IDR & Col_3_Pin) == 0) {
//            return 0b1001; // Binary representation of '9'
//        }
//    }
//
//    // Reset ROW4 and set other rows
//    ROW_PORT->BRR = Row_4_Pin;
//    ROW_PORT->BSRR = (Row_1_Pin | Row_2_Pin | Row_3_Pin);
//
//    // Check COL1
//    if ((GPIOC->IDR & Col_1_Pin) == 0) {
//        while ((GPIOC->IDR & Col_1_Pin) == 0) {
//            return 0b1010; // Binary representation of '*'
//        }
//    }
//    // Check COL2
//    if ((GPIOC->IDR & Col_2_Pin) == 0) {
//        while ((GPIOC->IDR & Col_2_Pin) == 0) {
//            return 0b0000; // Binary representation of '0'
//        }
//    }
//    // Check COL3
//    if ((GPIOC->IDR & Col_3_Pin) == 0) {
//        while ((GPIOC->IDR & Col_3_Pin) == 0) {
//            return 0b1011; // Binary representation of '#'
//        }
//    }
//
//    // Default return value if no key is pressed
//    return 0b1111; // Binary representation of '15'
//}


int Keypad_WhichKeyIsPressed(void) {
// detect and encode a pressed key at {row,col}
// assumes a previous call to Keypad_IsAnyKeyPressed() returned TRUE
// verifies the Keypad_IsAnyKeyPressed() result (no debounce here),
// determines which key is pressed and returns the encoded key ID

   int8_t iRow=0, iCol=0, iKey=0;  // keypad row & col index, key ID result
   int8_t bGotKey = 0;             // bool for keypress, 0 = no press

   ROW_PORT->BSRR = ROW_PINS;                       	 // set all columns HI
   for ( iCol = 0; iCol < NUM_ROWS; iCol++ ) {      	 // check all ROWS
      if ( COL_PORT->IDR & (BIT0 << iCol) ) {      	 // keypress in iRow!!
         ROW_PORT->BRR = ( ROW_PINS );            	 // set all cols LO
         for ( iRow = 0; iRow < NUM_COLS; iRow++ ) {   // 1 col at a time
            ROW_PORT->BSRR = ( BIT0 << (4+iRow) );     // set this col HI
            if ( COL_PORT->IDR & (BIT0 << iCol) ) {    // keypress in iCol!!
               bGotKey = 1;
               break;                                  // exit for iCol loop
            }
         }
         if ( bGotKey )
            break;
      }
   }
   //	encode {iRow,iCol} into LED word : row 1-3 : numeric, ‘1’-’9’
   //	                                   row 4   : ‘*’=10, ‘0’=15, ‘#’=12
   //                                    no press: send NO_KEYPRESS
   if ( bGotKey ) {
      iKey = ( iRow * NUM_COLS ) + iCol + 1;  // handle numeric keys ...
 	return( iKey );                         // return encoded keypress
   }
   return( 9 );                     // unable to verify keypress
}

