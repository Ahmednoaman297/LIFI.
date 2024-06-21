#include "tempadc.h"
#include "tm4c123gh6pm.h"



uint32 temp_read(void)
{
  unsigned int adc_value;
  
  ADC0_PSSI_R |= (1<<3);        /* Enable SS3 conversion or start sampling data from AN0 */
  while((ADC0_RIS_R & 8) == 0) ;   /* Wait untill sample conversion completed*/
  adc_value = ADC0_SSFIFO3_R; /* read adc coversion result from SS3 FIFO*/
  ADC0_ISC_R = 8;          /* clear coversion clear flag bit*/
  /*control Green PF3->LED */
  return adc_value;
}