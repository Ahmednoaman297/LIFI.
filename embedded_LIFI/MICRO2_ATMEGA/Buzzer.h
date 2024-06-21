/*
 * Buzzer.h
 *
 *  Created on: Nov 2, 2023
 *      Author: Ahmedmohamed
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include"gpio.h"
#define buzzer_PORT_ID  PORTC_ID
#define buzzer_PIN_ID  PIN5_ID

void Buzzer_init();
void Buzzer_on(void);
void Buzzer_off(void);


#endif /* BUZZER_H_ */
