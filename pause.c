#include "tm4c123gh6pm.h"
#include "delays.h"
#include "lcd_drivers.h"
#include "leds_on.h"
#include "leds_off.h"
int pause(void)
{ int i;
	delay_milli(1000);  
	while(1)
	{ delay_milli(200); 
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R^0x0E;
	   if (((GPIO_PORTF_DATA_R &0x01)==0) &&!(GPIO_PORTA_DATA_R &0x08)==0) 
		 { leds_on();
		 return 0;   }
	    if (((GPIO_PORTF_DATA_R &0X10)==0)&&(!(GPIO_PORTA_DATA_R &0x08)==0))  
 	{
	     LCD4bits_Cmd(0x01);
        leds_off();	      
		return 1;
	}

}
 }