/*
 * led.h
 *
 *  Created on: Dec 25, 2023
 *      Author: Ahmedmohamed
 */

#ifndef LED_H_
#define LED_H_
#include"gpio.h"
#define LED_PORT_ID  PORTC_ID
#define LED_PIN_ID  PIN0_ID

void Led_init(void);
void Led_on(void);
void Led_off(void);


#endif /* LED_H_ */
