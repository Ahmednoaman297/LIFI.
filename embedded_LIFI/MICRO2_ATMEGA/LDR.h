/*
 * LDR.h
 *
 *  Created on: Dec 25, 2023
 *      Author: Ahmedmohamed
 */

#ifndef LDR_H_
#define LDR_H_
#include "gpio.h"
#include "std_types.h"

#define LDR_PORT_ID  PORTB_ID
#define LDR_PIN_ID   PIN0_ID


#define FRAME_ultra 2
#define FRAME_limit_switch 0
#define FRAME_flame  3
#define buzzer_off 6


void LDR_ON(void);
uint8 LDR_RECIVE(void);

#endif /* LDR_H_ */
