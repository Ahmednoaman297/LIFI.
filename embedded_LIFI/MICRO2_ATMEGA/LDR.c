/*
 * LDR.c
 *
 *  Created on: Dec 25, 2023
 *      Author: Ahmedmohamed
 */
#include "LDR.h"
#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "lcd.h"
#include "gpio.h"
#include "LDR.h"
#include "Buzzer.h"
#include "led.h"

uint8 morth_counter=0;
uint8 data_counter=0;
uint8 flag=0;
uint8 data[3];

void LDR_ON(void) {
	GPIO_setupPinDirection(LDR_PORT_ID, LDR_PIN_ID, PIN_INPUT);
}

uint8 LDR_RECIVE(void) {
	morth_counter = 0;
	flag = 0;
//	LCD_clearScreen();
	uint8 temp = 0;
	LCD_moveCursor(0, 0);
	LCD_displayString("bd2na");
	Buzzer_off();
	for (int i = 10; i > 0; i--) {
		LCD_moveCursor(0, 8);

		LCD_intgerToString(i);
		_delay_ms(500);

	}
	while (morth_counter != 1) {

		if (GPIO_readPin(LDR_PORT_ID, LDR_PIN_ID) == LOGIC_LOW) {
			morth_counter++;
			_delay_ms(1000);

		}

	}

	LCD_clearScreen();
	while (data_counter != 2) {
		morth_counter++;
		if (GPIO_readPin(LDR_PORT_ID, LDR_PIN_ID) == LOGIC_LOW) {
			data[data_counter] = 1;
		} else {
			data[data_counter] = 0;
		}
		data_counter++;
		_delay_ms(1000);

	}
	while (morth_counter < 3) {
		if (GPIO_readPin(LDR_PORT_ID, LDR_PIN_ID) == LOGIC_LOW)
		{
			_delay_ms(1000);
			morth_counter++;
		}

	}
	for (char i = 0; i < 2; i++) {
		LCD_intgerToString(data[i]);
		_delay_ms(1000);
	}
	for (uint8 i = 0; i < 3; i++) {
		temp = temp | (data[i] << i);
	}
	return temp;
}
