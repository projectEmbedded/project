#include "tm4c123gh6pm.h"
void leds_off(void)
{
 GPIO_PORTF_DATA_R&=~0x0E;

}