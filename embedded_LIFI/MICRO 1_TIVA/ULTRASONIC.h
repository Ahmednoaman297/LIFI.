/*
 * ULTRASONIC.h
 *
 *  Created on: Oct 18, 2023
 *      Author: Ahmedmohamed
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "GPIO.h"
//SETUP TRIGGER
#define TRIGGER_PORT_ID  PORTA_ID
#define TRIGGER_PIN_ID   PIN3_ID
//SETUP ECHO
#define ECHO_PORT_ID  PORTB_ID
#define ECHO_PIN_ID   PIN6_ID
//FUNCTION PROTOTYPE
void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);
void display_distance(void);




#endif /* ULTRASONIC_H_ */
