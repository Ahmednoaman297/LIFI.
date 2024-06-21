/*
 * MAIN.c
 *
 *  Created on: Dec 25, 2023
 *      Author: Ahmedmohamed
 */

#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "lcd.h"
#include "gpio.h"
#include "LDR.h"
#include "Buzzer.h"
#include "led.h"
#include "avr/io.h"
/*
 uint8 morth_counter=0;
 uint8 data_counter=0;
 uint8 data[3];
 uint8 flag=0;

 */
uint8 data = 0;

int main(void) {
	Buzzer_init();
	Led_init();
	LCD_init();
	LDR_ON();
	//Buzzer_on();
	while (1) {
		LCD_clearScreen();
		data = 0;
		data = LDR_RECIVE();

		switch (data) {
		 case FRAME_limit_switch:
		 LCD_moveCursor(1, 0);
		 LCD_displayString("DOOR OPENED");
		 LCD_moveCursor(1, 0);
		 Buzzer_on();
		 _delay_ms(5000);
		 break;
		 case FRAME_flame:
		 LCD_moveCursor(1, 0);
		 LCD_displayString("fire detected");
		 LCD_moveCursor(1, 0);
		 Buzzer_on();
		 _delay_ms(5000);

		 break;
		 case FRAME_ultra:
		 LCD_moveCursor(1, 0);
		 LCD_displayString("us detect object");
		 Buzzer_on();
		 _delay_ms(5000);

		 break;
		 case buzzer_off:
		 Buzzer_off();
		 Led_off();
		 break;
		 }

	}}
