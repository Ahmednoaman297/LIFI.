/* * led.c
 *
 *  Created on: Dec 25, 2023
 *      Author: Ahmedmohamed
 */
#include <util/delay.h> /* For the delay functions */
#include "led.h"
#include "gpio.h"
void Led_init(void)
{
	GPIO_setupPinDirection(LED_PORT_ID,LED_PIN_ID,PIN_OUTPUT);
	GPIO_writePin( LED_PORT_ID, LED_PIN_ID , LOGIC_LOW);
}
void Led_on(void)
{
	GPIO_writePin( LED_PORT_ID, LED_PIN_ID , LOGIC_HIGH);
}
void Led_off(void)
{

	GPIO_writePin( LED_PORT_ID, LED_PIN_ID , LOGIC_LOW);

}
