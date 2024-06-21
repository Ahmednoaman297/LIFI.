 /******************************************************************************
 *
 * Module: TIMERS
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR ICU driver
 *
 * Author: Ahmed mohamed
 *
 *******************************************************************************/

#ifndef TIMERS_H_
#define TIMERS_H_

#include "std_types.h"
//*******************************************************************************
 /*                         Types Declaration                                   */
 //*******************************************************************************//
   
   
   //struct without interrupt
typedef enum
{
   BIT32,RTC,BIT16=4
}BITS_CONFIGURATION;
typedef enum
{
  TIMER0,TIMER1,TIMER2,TIMER3,TIMER4,TIMER5 
}TIMER_TYPE;
typedef enum
{
  one_shot=1,periodic_mode,capture_mode
}TIMER_count;
typedef enum
{
  down,up
}TIMER_direction;
typedef enum
{
	prior_0,prior_1,prior_2,prior_3,prior_4,prior_5,prior_6,prior_7
}prior;
typedef enum
{
	TIMER0A=19,TIMER0B,TIMER1A,TIMER1B,TIMER2A,TIMER2B,TIMER3A=35,TIMER3B,TIMER4A=70,TIMER4B,TIMER5A=92,TIMER5B
}irq;
typedef struct
{
  BITS_CONFIGURATION MODE;
  TIMER_TYPE TIMER_NO;
  TIMER_count counts;
  TIMER_direction dir;
  prior pr;
  irq IRQ;
}SETUP_TIMER;



void Timers_Init_interrupt(const SETUP_TIMER *ptr);


void Timers_Init(const SETUP_TIMER *ptr);
void capture_modes(void);
uint16 get_captured_valueS(void);


#endif /* TIMER_H_ */
