#include "tm4c123gh6pm.h"
#include "delays.h"
#include "lcd_drivers.h"
#include "timer.h"
void finished(void)
{   int k;
	  LCD4bits_Cmd(0x01);
		LCD_WriteString("finished");
		for(k=0;k<6;k++)
		{
      GPIO_PORTA_DATA_R =GPIO_PORTA_DATA_R^0x04;  // toggle the buzzer pin
			GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R^0x0E; //toggle the leds
		  delay_ms(500);
		}
		  GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R^0x0E;	
		LCD4bits_Cmd(0x01);
}