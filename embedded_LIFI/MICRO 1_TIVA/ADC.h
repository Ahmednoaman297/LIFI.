/*
 * ADC.h
 *
 *  Created on: Oct 9, 2023
 *      Author: Ahmedmohamed
 */

#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"
#include "tm4c123gh6pm.h"






void ADC_INIT(void );
uint16 ADC_READ(void);

#endif /* ADC_H_ */
