#include "tm4c123gh6pm.h"
#include "lcd_drivers.h"
#include "delays.h"
#include "keypad.h"
#include "timer.h"
#include "switches_inputs.h"
void weight_chicken(void)
{ int time,j;
 char n=get_keypad_input();
 buzzer();
  while (!(n>=(1+'0') && n<=(9+'0')))
		{  for(j=0;j<4;j++)
				{ 
					LCD4bits_Data(' ');
				
				}
			 LCD_WriteString("Err");
			 delay_ms(2000);
		   LCD4bits_Cmd(0x01);
			 LCD_WriteString("Chicken weight?");
		   delay_ms(2000);	                 
		   LCD4bits_Cmd(0x01);
			 n=get_keypad_input(); 
		         buzzer();
			 delay_ms(2000);
			}
		
		    delay_milli(1000);
			  LCD4bits_Data(n);
			  delay_milli(2000);	
	      LCD4bits_Cmd(0x01);
       
			 time=((n-'0'))*12;    
			 if(time>60)
			 {
				while(!(GPIO_PORTF_DATA_R&0x01)==0 || (GPIO_PORTA_DATA_R&0X08)==0);
			  timer(time/60,(time%60));
			 
			 }
			 else
			 {
				 while(!(GPIO_PORTF_DATA_R&0x01)==0 || (GPIO_PORTA_DATA_R&0X08)==0);
				 timer(0,time); 
			 } 
			 

		}
