#include "tm4c123gh6pm.h"
#include "common_macros.h"
#include "GPIO.h"
#include "lcd.h"
#include "ULTRASONIC.h"
#include "ADC.h"
#include "UART.h"
#include "systick.h"
#include "INTERRUPT.h"
uint8 flag_m=0;
uint8 flag = 0;
uint16 flame_value=0;
uint16 ultra_Value=0;
uint8 flame=0;
void GPIOB_Handler(void)
{
  if(!GPIO_readPin(PORTB_ID,PIN5_ID))
  {
    flag_m=1;
  }
  GPIO_PORTB_ICR_R|=(1<<5);
  flag_m=0;
}
void GPIOF_Handler(void)
{
  if(!GPIO_readPin(PORTF_ID,PIN4_ID))
  {
    flag=0;
  }
  else if(!(GPIO_readPin(PORTF_ID,PIN0_ID)))
  {
    flag=1;
    LCD_clearScreen();
    LCD_displayString("system closed");
  }
  
  //clear two flags 
  GPIO_PORTF_ICR_R |= 0x11;
}
void frame_muteBuzzer(void)
{
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);
  delay_ms(1000);
  
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);
  delay_ms(1000);
  CLEAR_BIT(GPIO_PORTB_DATA_R,PIN7_ID);//FRAME
  delay_ms(1000);
  
  
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);//STOP BIT
}
void Frame_ultra(void)
{
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);
  delay_ms(1000);
  
  
  
  CLEAR_BIT(GPIO_PORTB_DATA_R,PIN7_ID);//FRAME
  delay_ms(1000);
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);
  delay_ms(1000);
  
 
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);//STOP BIT
      delay_ms(1000);


}
void Frame_switch(void)
{
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);
  delay_ms(1000);
   
  CLEAR_BIT(GPIO_PORTB_DATA_R,PIN7_ID);//FRAME
  delay_ms(1000);
  CLEAR_BIT(GPIO_PORTB_DATA_R,PIN7_ID);//FRAME
  delay_ms(1000);

  
  
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);//STOP BIT
    delay_ms(1000);
}
void Frame_Flame(void)
{
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);
  delay_ms(1000);
  
  
  
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);
  delay_ms(1000);
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);
    delay_ms(1000);

  
  SET_BIT(GPIO_PORTB_DATA_R,PIN7_ID);//STOP BIT
}
int main()
{
  uint8 counter=0; 
  // GPIO and LED initialization
  Gpio_init_Allports();
  //
  GPIO_PORTF_CR_R |= 0x11;
  GPIO_PORTF_DIR_R &= 0XEE;
  GPIO_PORTF_DEN_R |= 0X11;
  GPIO_PORTF_PUR_R|=0X11;
  //
  
  
  //setup mute button PB5
  GPIO_PORTB_CR_R |= (1<<5);
  GPIO_PORTB_DIR_R &= ~(1<<5);
  GPIO_PORTB_DEN_R |= (1<<5);
  GPIO_PORTB_PUR_R|=(1<<5);
  //setup switch
  GPIO_setupPinDirection(PORTA_ID,PIN2_ID,PIN_INPUT);
  //
  //setup trans led
  GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT);
  
  //LCD INIT
  LCD_init();
  //ADC INIT
  ADC_INIT() ;
  //ULTRA INIT
  Ultrasonic_init();
  //BLUETOOTH INIT
  UART_init();
  //
  configuration_int SETUP= {FALLING,0x11,EDGE,IBE,PORTF_ID,prior_1};
  INTERRUPT_INIT(&SETUP);  
  
  while (1)
    
  {
   
    if(flag!=1)
    {
      if(flag_m==1){
        frame_muteBuzzer();
        LCD_displayString("BUZEER MUTED");
        UART_Send_String("BUZEER MUTED");
        
      }
      GPIO_writePin(PORTF_ID,PIN4_ID,LOGIC_HIGH);
      CLEAR_BIT(GPIO_PORTB_DATA_R,PIN7_ID);
      LCD_clearScreen();
      LCD_moveCursor(0,0);
      LCD_displayString("SS start after");
      counter=10;
      while(counter>0 && !(flag))
      {
        LCD_moveCursor(0,15);
        
        LCD_intgerToString(counter);
        delay_ms(500);
        counter--;
      }
      if(flag==1){continue;}
      LCD_clearScreen();
      LCD_displayString("SS start now");
      //READINGS
      ultra_Value=Ultrasonic_readDistance();
      flame_value=ADC_READ();
      
      if(ultra_Value<=10)
      {
        LCD_moveCursor(1,0);
        LCD_displayString("us detect object\n");
        UART_Send_String("us detect object");
        Frame_ultra();
        LCD_clearScreen();
      }
      
      else if(flame_value>500)
      {
        if(flame==0){
        LCD_moveCursor(1,0);
        LCD_displayString("sensor detect fire");
        UART_Send_String("sensor detect fire\n");
        Frame_Flame();
        LCD_clearScreen();
        }
      }
      else if(GPIO_readPin(PORTA_ID,PIN2_ID)==LOGIC_LOW)
      {
        LCD_moveCursor(1,0);
        LCD_displayString("DOOR OPENED");
        UART_Send_String("DOOR OPENED\n");
        Frame_switch();
        
        LCD_clearScreen(); 
      }
      
      
    }
    
  }
}
