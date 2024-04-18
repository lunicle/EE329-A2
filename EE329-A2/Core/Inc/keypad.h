/*
 * keypad.h
 *
 *  Created on: Apr 14, 2024
 *      Author: James Pan
 */

#ifndef KEYPAD_H
#define KEYPAD_H
#include "keypad.h"
#include "stdint.h"

#define Row_1_Pin GPIO_PIN_0
#define Row_1_GPIO_Port GPIOC
#define Row_2_Pin GPIO_PIN_1
#define Row_2_GPIO_Port GPIOC
#define Row_3_Pin GPIO_PIN_2
#define Row_3_GPIO_Port GPIOC
#define Row_4_Pin GPIO_PIN_3
#define Row_4_GPIO_Port GPIOC
#define Col_1_Pin GPIO_PIN_4
#define Col_1_GPIO_Port GPIOC
#define Col_2_Pin GPIO_PIN_5
#define Col_2_GPIO_Port GPIOC
#define Col_3_Pin GPIO_PIN_6
#define Col_3_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_8
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_9
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_10
#define LED3_GPIO_Port GPIOC
#define LED4_Pin GPIO_PIN_11
#define LED4_GPIO_Port GPIOC
#define ROW_PORT GPIOC
#define COL_PORT GPIOC
#define NUM_ROWS 4
#define NUM_COLS 3
#define ROW_PINS (Row_1_Pin | Row_2_Pin | Row_3_Pin | Row_4_Pin)
#define COL_PINS (Col_1_Pin | Col_2_Pin | Col_3_Pin)

int keypad_anykey(void);
uint8_t keypad_readkey(void);
int Keypad_IsAnyKeyPressed(void);

#endif // KEYPAD_H
