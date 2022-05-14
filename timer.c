#include "lcd_drivers.h"
#include"delays.h"
#include"leds_on.h"
void timer(int m,int s)
{ int y;
int j=m;
int i=s;
leds_on();

  for(; j>=0 ; j--)                       // minute parameter 
	{
	for (; i>=0 ;i--)                   // second parameter
	{
		for(y=0 ; y<4 ;y++)  
		{
		  LCD4bits_Data(' ');          // displaying 4 spaces to center the count down time
		}	
	
	  LCD4bits_Data((j/10)+'0');         // tens of minute
	  LCD4bits_Data((j%10)+'0');        // units of minute
	  LCD4bits_Data(':');
	  LCD4bits_Data((i/10) +'0');       // tens of second
	  LCD4bits_Data((i%10)+'0');       // units of second 
    delay_ms(1000);                     // wait for 1 second
	  LCD4bits_Cmd(0x01);             // clear lcd display 
	 
	}
 
i=59;                                 // reset second every minute
}
  
}
