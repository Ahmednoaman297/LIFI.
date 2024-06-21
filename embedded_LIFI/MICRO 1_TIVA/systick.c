/*
 * systick.c
 *
 *  Created on: Nov 21, 2023
 *      Author: Ahmed mohamed
 */

#include "systick.h"
#include "std_types.h"
#include "tm4c123gh6pm.h"
#include "common_macros.h"

void SYSTICK_disable(void)
{
  //disable systick timer to avoid any garbage 
      NVIC_ST_CTRL_R =0 ;
      
}
void SYSTICK_enable(void)
{
      NVIC_ST_CTRL_R |= 0x05 ;

}
uint32 systickPeriodGet(void)
{
   return NVIC_ST_RELOAD_R;
}
void systickPeriodSet(uint32 period)
{
    uint32 no_of_ticks=0;
uint32 COUNT=0;
  SYSTICK_disable();
  
      NVIC_ST_CURRENT_R = 0 ;
      
      no_of_ticks=((period*16000000))-1;
      SYSTICK_enable();
     NVIC_ST_RELOAD_R= no_of_ticks;
      while(COUNT < period)
    {
        /*
         * wait until the flag is set
         */
        if( GET_BIT(NVIC_ST_CTRL_R ,16) )
        COUNT ++ ;
    }
}
uint32 systickValueGet(void)
{
  return NVIC_ST_CURRENT_R;
}
boolean Systick_is_Time(void)
{
        /*
         * wait until the flag is set
         */
        if( GET_BIT(NVIC_ST_CTRL_R ,16) )
          return TRUE;
        else
          return FALSE;
}
