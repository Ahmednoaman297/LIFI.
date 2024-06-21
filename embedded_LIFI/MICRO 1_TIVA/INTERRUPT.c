/******************************************************************
*  File Name: INTERRUPT.c
*
*  Description: A file that contain the definitions for PORTF pins
*
*  Created on: DEC 19, 2023
*
*  Author: Ahmed Mohamed
******************************************************************/
#include "INTERRUPT.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"

//**************************************************************************************************************************************************//
//***********************************************interrrupt************************************************************//
void INTERRUPT_INIT(const configuration_int* ptr)
{
  /*
  * unlock the unlock register to be able to change the values in PF0
  */
  //00000011
  /*
  * Disable the analog on PF0 and PF1
  
  /*
  * Enable the priority of the switch in PRIn
  */
  NVIC_PRI7_R &= ~(7<<21) ;
  NVIC_PRI7_R |=  (1<<21) ;
  
  NVIC_PRI0_R|=(1<<5);
  
  /*
  * Enable the interrupt for PORTF
  */
  NVIC_EN0_R |= (1<<30) ;
  /*
  * Enable the interrupt for PORTB
  */
  NVIC_EN0_R |= (1<<1) ;
  
  /*
  * set the switch to trigger interrupt on edges
  */
  GPIO_PORTF_IS_R &= ~(1<<0) ;
  GPIO_PORTF_IS_R &= ~(1<<4) ;
  
  
  /*
  * configure the switch to trigger interrupt on the falling edge
  */
  GPIO_PORTF_IBE_R &= ~(1<<0) ;
  GPIO_PORTF_IEV_R &= ~(1<<0) ;
  GPIO_PORTF_IBE_R &= ~(1<<4) ;
  GPIO_PORTF_IEV_R &= ~(1<<4) ;
  //
  GPIO_PORTB_IBE_R &= ~(1<<5) ;
  GPIO_PORTB_IEV_R &= ~(1<<5) ;
  /*
  * Enable interrupt for pin0,pin4,pin5 portB
  */
  GPIO_PORTF_IM_R |= (1<<0) ;
  GPIO_PORTF_IM_R |= (1<<4) ;
  //
  GPIO_PORTB_IM_R |= (1<<5) ;
  
  /*
  * clear the flag
  */
  GPIO_PORTF_ICR_R |= (1<<0) ;
  GPIO_PORTF_ICR_R |= (1<<4) ;
  //
  GPIO_PORTB_ICR_R |= (1<<5) ;
  
  
}
