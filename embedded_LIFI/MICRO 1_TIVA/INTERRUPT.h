/******************************************************************
 *  File Name: INTERRUPT.c
 * 
 *  Created on: DEC 19, 2023
 *
 *  Author: Ahmed Mohamed
 ******************************************************************/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "std_types.h"
#include "GPIO.h"



typedef enum
{
	FALLING,RISING,LOW_level,HIGH_level
}INTERRUPT_EDGE_TYPE;
typedef enum
{
	EDGE,LEVEL
}TYPE_INTERRUPT;
typedef enum
{
	IBE,IEV
}TRIGGER;
typedef enum
{
	prior_0,prior_1,prior_2,prior_3,prior_4,prior_5,prior_6,prior_7
}prior;
typedef struct {
  INTERRUPT_EDGE_TYPE edge;
  
  uint8 hexa_decimal_pin;
  
  TYPE_INTERRUPT mode;
  
    TRIGGER trig;
    
    uint8 port;
    
    prior priority;
    
}configuration_int;
void INTERRUPT_INIT(const configuration_int* ptr);
#endif /* INTERRUPT_H_ */
