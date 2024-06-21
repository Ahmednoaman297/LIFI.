/*
 * ICU.c
 *
 *  Created on: Oct 19, 2023
 *      Author: Ahmed mohamed
 */

#include "ICU.h"
#include "timers.h"
#include "tm4c123gh6pm.h"
#include "ULTRASONIC.h"
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

void Timer0A_Handler(void)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


void ICU_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

void capture_modes(void)
{
  SYSCTL_RCGCTIMER_R|=1;/* enable clock to Timer Block 0 */
  
  GPIO_PORTB_DIR_R &= ~0x40;/* make PB6 an input pin */
  GPIO_PORTB_DEN_R |= 0x40;
  GPIO_PORTB_AFSEL_R|=0x40;/* make PB6 as digital pin */
  GPIO_PORTB_PCTL_R &= ~0x0F000000;
  GPIO_PORTB_PCTL_R |= 0x07000000;
  
  TIMER0_CTL_R &= ~1; /* disable timer0A during setup */
  TIMER0_CFG_R = 4; /* 16-bit timer mode */
  TIMER0_TAMR_R = 0x17; /* up-count, edge-time, capture mode */
 // TIMER0_CTL_R &= ~0x0C;
  TIMER0_CTL_R |=0x0C;
  TIMER0_ICR_R |= 0x04;
  TIMER0_IMR_R |= 0X04;
        
  NVIC_EN0_R=(1<<19);
  TIMER0_CTL_R|=(1<<0);
  
  
}
uint16 get_captured_valueS(void)
{
  uint8 thisEdge=0,lastEdge=0;
  Ultrasonic_Trigger();
  while((TIMER0_RIS_R & 4) == 0) ; /* wait till captured */
  lastEdge = TIMER0_TAR_R; /* save the timestamp */
  /* capture the second rising edge */
  TIMER0_ICR_R = 4; /* clear timer0A capture flag */
  while((TIMER0_RIS_R & 4) == 0) ; /* wait till captured */
  thisEdge = TIMER0_TAR_R; /* save the timestamp */
  return (thisEdge - lastEdge) & 0x00FFFFFF; /* return the time difference */
}
