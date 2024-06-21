/*
 * systick.h
 *
 * Created on: Nov 21, 2023
 *      Author: Ahmed mohamed
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "std_types.h"
#include <stdio.h>
void SYSTICK_disable(void);
void SYSTICK_enable(void);
uint32 systickPeriodGet(void);
void systickPeriodSet(uint32 period);
uint32 systickValueGet(void);
boolean Systick_is_Time(void);

#endif /* SYSTICK_H_ */
