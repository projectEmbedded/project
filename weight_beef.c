#include "tm4c123gh6pm.h"
#include "lcd_drivers.h"
#include "delays.h"
#include "keypad.h"
#include "timer.h"
#include "switches_inputs.h"
void weight_beef(void)
 {
	
	 
  int time,j;
  char n=get_keypad_input();               // WE GET THE KEYPAD INPUT TO KNOW THE NUMBER OF KILOS
   buzzer();				    // we make the function buzer to make sound for every time we press on the keypad 
	  
	 while (!(n<=(9+'0') && n>=(1+'0')))    // this loop to make sure that the number we get from the keypad is between 1 and 9            
			{ 
			   spaces(4);                            //  printing spaces on the lcd and make any thing in the center 
			LCD_WriteString("Err");     		 // if the number of kilos not in between of 1 and 9 the lcd will display "ERR"
			 delay_ms(2000);			 // we make delay then show the next command 
		   LCD4bits_Cmd(0x01);				 // clear the LCD 
			 LCD_WriteString("Beef weight?");  	 // then show th text ("Beef weight?") on the LCD 
		   delay_ms(2000);	                 	 // we make delay then show the next command 
		   LCD4bits_Cmd(0x01);				 // clear the LCD 
			 n=get_keypad_input(); 			 // after clearing the LCD we get another input to make sure it is between 1 and 9 
                         buzzer();			
			 delay_ms(2000);
			}
		                delay_ms(1000);			 // if the number is valid then we will wait for delay 
			       LCD4bits_Data(n);		 // display th number of kilos on the LCD
			       delay_ms(2000);	
	                     LCD4bits_Cmd(0x01);				 // clear the LCd 
       
			 time=((n-'0'))*30;    			 // calculate the time after get the number of kilos 
			 if(time>60)			 // make sure that the number if larger thean 60 sec then it will be converted to minutes and seconds 
			 {
				while(!(GPIO_PORTF_DATA_R&0x01)==0 || (GPIO_PORTA_DATA_R&0X08)==0);  // the while loop to make sure that sw2 is pressed and sw3 open	
			  timer(time/60,(time%60)); 			 // get the minutes and the seconds for the function timer 
			 }
			 else			 // if the number is not more than 60 seconds it will be converted to seconds only 
			 {
				 while(!(GPIO_PORTF_DATA_R&0x01)==0 || (GPIO_PORTA_DATA_R&0X08)==0);   // the while loop to make sure that sw2 is pressed and sw3 open
				 timer(0,time); 			 // the timer input (seconds only)
			 } 
			 
 }
