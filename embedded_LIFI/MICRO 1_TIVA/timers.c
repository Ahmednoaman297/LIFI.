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

#include "timers.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

void Timers_Init(const SETUP_TIMER *ptr)
{
  
  SYSCTL_RCGCTIMER_R |=(1<<ptr->TIMER_NO);
  switch(ptr->TIMER_NO)
  {
    
    case(TIMER0):
      //disable timer
      TIMER0_CTL_R=0;
      //bit type
      TIMER0_CFG_R=(ptr->MODE);
      //one shot or periodic
      TIMER0_TAMR_R|=ptr->counts;
      //count down or up
      switch(ptr->dir)
      {
        case(down):
          TIMER0_TAMR_R&=~(1<<4);//TACDIR REG
          
          break;
          case(up):
            TIMER0_TAMR_R|=(1<<4);
            
            break;
      }
      //load time interval
      TIMER0_TAILR_R=16000-1;
      //load prescaler
      TIMER0_TAPR_R=256-1;
      //clear timeout flag
      TIMER0_ICR_R|=(1<<ptr->TIMER_NO);
      //enable timer
      TIMER0_CTL_R|=(1<<ptr->TIMER_NO);
      
      
      
      
      
      
      
      
      
      
      
      
      
      break;
      case(TIMER1):
        TIMER1_CFG_R |=ptr->MODE;
        TIMER1_CTL_R=0;
        //bit type
        TIMER1_CFG_R=(ptr->MODE);
        //one shot or periodic
        TIMER1_TAMR_R|=ptr->counts;
        //count down or up
        switch(ptr->dir)
        {
          case(down):
            TIMER1_TAMR_R&=~(1<<4);
            
            break;
            case(up):
              TIMER1_TAMR_R|=(1<<4);
              
              break;
        }
        //load time interval
        TIMER1_TAILR_R=16000-1;
        //load prescaler
        TIMER1_TAPR_R=256-1;
        //clear timeout flag
        TIMER1_ICR_R|=(1<<ptr->TIMER_NO);
        //enable timer
        TIMER1_CTL_R|=(1<<ptr->TIMER_NO);
        
        break;
        case(TIMER2):
          TIMER2_CFG_R |=ptr->MODE;
          TIMER2_CTL_R=0;
          
          break;
          case(TIMER3):
            TIMER3_CFG_R |=ptr->MODE;
            TIMER3_CTL_R=0;
            
            break;
            case(TIMER4):
              TIMER4_CFG_R |=ptr->MODE;
              TIMER4_CTL_R=0;
              
              break;
              case(TIMER5):
                TIMER5_CFG_R |=ptr->MODE;
                TIMER5_CTL_R=0;
                
                break;
  }
  
  
}
void Timers_Init_interrupt(const SETUP_TIMER *ptr)
{
  switch(ptr->TIMER_NO)
  {
    case(TIMER0):
      //ENABLE CLOCK FOR GPTM
      SYSCTL_RCGCTIMER_R|=(1<<ptr->TIMER_NO);
      //disable timer
      TIMER0_CTL_R=0;
      //bit type
      TIMER0_CFG_R=(ptr->MODE);
      //one shot or periodic
      TIMER0_TAMR_R|=ptr->counts;
      //count down or up
      switch(ptr->dir)
      {
        case(down):
          TIMER0_TAMR_R&=~(1<<4);
          
          break;
          case(up):
            TIMER0_TAMR_R|=(1<<4);
            
            break;
      }
      //load time interval
      TIMER0_TAILR_R=16000-1;
      //load prescaler
      TIMER0_TAPR_R=256-1;
      //clear timeout flag
      TIMER0_ICR_R|=(1<<ptr->TIMER_NO);
      
      //set prtiority
      NVIC_PRI4_R=(ptr->pr)<<29;
      //unmask timer
      TIMER0_IMR_R |=(1<<ptr->TIMER_NO);
      //enable timer interrupt
      NVIC_EN0_R=(1<<TIMER0A);
      //enable timer
      TIMER0_CTL_R|=(1<<ptr->TIMER_NO);
      
      break;
      case(TIMER1):
        TIMER1_CFG_R |=ptr->MODE;
        TIMER1_CTL_R=0;
        //bit type
        TIMER1_CFG_R=(ptr->MODE);
        //one shot or periodic
        TIMER1_TAMR_R|=ptr->counts;
        //count down or up
        switch(ptr->dir)
        {
          case(down):
            TIMER1_TAMR_R&=~(1<<4);
            
            break;
            case(up):
              TIMER1_TAMR_R|=(1<<4);
              
              break;
        }
        //load time interval
        TIMER1_TAILR_R=16000-1;
        //load prescaler
        TIMER1_TAPR_R=256-1;
        //clear timeout flag
        TIMER1_ICR_R|=(1<<ptr->TIMER_NO);
        //enable timer
        TIMER1_CTL_R|=(1<<ptr->TIMER_NO);
        
        case(TIMER2):
          TIMER2_CFG_R |=ptr->MODE;
          TIMER2_CTL_R=0;
          
          break;
          case(TIMER3):
            TIMER3_CFG_R |=ptr->MODE;
            TIMER3_CTL_R=0;
            
            break;
            case(TIMER4):
              TIMER4_CFG_R |=ptr->MODE;
              TIMER4_CTL_R=0;
              
              break;
              case(TIMER5):
                TIMER5_CFG_R |=ptr->MODE;
                TIMER5_CTL_R=0;
                
                break;
  }
  
  
  
}
