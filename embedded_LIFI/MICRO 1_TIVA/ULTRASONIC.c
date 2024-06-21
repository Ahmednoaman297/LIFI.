#include "ULTRASONIC.h"
#include "timers.h"
#include "systick.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "common_macros.h"
#include "ICU.h"
static uint16 ultrasonic_time = 0;
static   uint16 thisEdge=0,lastEdge=0;

void Ultrasonic_init(void) {
  // Initialize GPIO and Timer for Ultrasonic sensor
  GPIO_setupPinDirection(TRIGGER_PORT_ID, TRIGGER_PIN_ID, PIN_OUTPUT);
  
  // Add other necessary initializations...
  
  // Initialize Timer0A for capture mode
  capture_modes();
  
  // Set the callback function for Timer0A interrupt
  ICU_setCallBack(Ultrasonic_edgeProcessing);
}

void Ultrasonic_Trigger(void) {
  GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_HIGH);
  delay_ms(10);
  GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void) {
  uint16 DISTANCE_CM = 0;
  Ultrasonic_Trigger();

  //ultrasonic_counter = 0;
  DISTANCE_CM = (ultrasonic_time)*(0.0010625);
  return DISTANCE_CM;
}

void Ultrasonic_edgeProcessing(void) {
  if (GET_BIT(GPIO_PORTB_DATA_R,6)==1)
  {
    thisEdge = TIMER0_TAR_R;
    TIMER0_ICR_R = 4;//CLEAR FLAG
    
  }
  else if (GET_BIT(GPIO_PORTB_DATA_R,6)==0)
  {
    lastEdge = TIMER0_TAR_R;
    TIMER0_ICR_R = 4;//CLEAR FLAG
  }
  ultrasonic_time= (lastEdge-thisEdge  );
}

