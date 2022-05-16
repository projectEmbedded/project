#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "math.h"
#include "stdlib.h"
#include "delays.h"
#include "lcd_drivers.h"
#include "keypad.h"
#include "PortInit.h" 
#include "timer.h"
#include "leds_on.h"
#include "switches_inputs.h"

char temp0,temp1,temp2,temp3;
int h;

void weight_beef(void)
 {
	
	 
  int time,j;
  char n=get_keypad_input(); 
	  
	 while (!(n<=(9+'0') && n>=(1+'0')))              
			{ 
			 for(j=0;j<4;j++)
				{ 
					LCD4bits_Data(' ');
				
				}
			 LCD_WriteString("Err");
			 delay_ms(2000);
		   LCD4bits_Cmd(0x01);
			 LCD_WriteString("Beef weight?");
		   delay_ms(2000);	                 
		   LCD4bits_Cmd(0x01);
			 n=get_keypad_input(); 
			 delay_ms(2000);
			}
		         delay_milli(1000);
			       LCD4bits_Data(n);
			       delay_milli(2000);	
	           LCD4bits_Cmd(0x01);
       
			 time=((int)(n-'0'))*30;    
			 if(time>60)
			 {
				while(!(GPIO_PORTF_DATA_R&0x01)==0);
			  timer(time/60,(time%60));
			 }
			 else
			 {
				 while(!(GPIO_PORTF_DATA_R&0x01)==0);
				 timer(0,time); 
			 } 
			 
 }
 
void weight_chicken(void)
{ int time,j;
 char n=get_keypad_input();
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
			 delay_ms(2000);
			}
		
		    delay_milli(1000);
			  LCD4bits_Data(n);
			  delay_milli(2000);	
	      LCD4bits_Cmd(0x01);
       
			 time=((int)(n-'0'))*12;    
			 if(time>60)
			 {
				while(!(GPIO_PORTF_DATA_R&0x01)==0);
			  timer(time/60,(time%60));
			 
			 }
			 else
			 {
				 while(!(GPIO_PORTF_DATA_R&0x01)==0);
				 timer(0,time); 
			 } 
			 

		}



 int pause(void)
{ int i;
	delay_milli(1000);  
	while(1)
	{
	   if (((GPIO_PORTF_DATA_R &0x01)==0) &&!(GPIO_PORTA_DATA_R &0x08)==0) 
		 {return 0;}
	    if (((GPIO_PORTF_DATA_R &0X10)==0)&&(!(GPIO_PORTA_DATA_R &0x08)==0))  
 	{
	     LCD4bits_Cmd(0x01);
	      	return 1;
	}

}
 }
void idle(void)
{
  
	while((GPIO_PORTA_DATA_R&0X08)==0);
	 


}
 
 void finished(void)
{   int k;
	  LCD4bits_Cmd(0x01);
		LCD_WriteString("finished");
		for(k=0;k<7;k++)
		{
			GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R^0x0E; //toggle the leds
		  delay_ms(500);
		}
				LCD4bits_Cmd(0x01);
}
	int main (void)
{ int y,z,h,j;
	char x,k,temp1,temp2,temp3,n;
Leds_init();
PortC_init();
PortE_init();
PortB_init();
LCD4bits_Init();	
switches();
 label :
  while(1)
 { 
   x=get_keypad_input();
	 
	switch(x)
 {
	case ('A'):                              
 {
  for(j=0;j<3;j++)
		{ 
			LCD4bits_Data(' ');
		}
	 LCD_WriteString("POPCORN");
 while(!(GPIO_PORTF_DATA_R&0x01)==0);
 delay_ms(1000);
 LCD4bits_Cmd(0x01);
 timer(1,0);
 
  break;
 }
	
case('B'):
		{
			for(j=0;j<2;j++)
				{ 
					LCD4bits_Data(' ');
				
				}
		 LCD_WriteString("Beef weight?");
		  delay_ms(2000);
		  LCD4bits_Cmd(0x01);
      delay_ms(1000);
     	weight_beef();
		break;
		}

   case ('C'):
{ 

	LCD_WriteString("Chicken weight?");
	 delay_milli(2000);
   LCD4bits_Cmd(0x01);
   delay_ms(1000);
   weight_chicken();
 
			break;
}
		
		case ('D'):
  {  
	LCD_WriteString("Cooking Time?");
  delay_ms(2000);
	LCD4bits_Cmd(0X01);
	LCD_WriteString("max 30 min");
	delay_ms(2000);
	LCD4bits_Cmd(0x01);
	for(h=0 ; h<4 ; h++)
{
    LCD4bits_Data(' ');      // printing 4 spaces
}
LCD_WriteString("00:00");    // writing (00:00) on lcd   00:01 >> 30:00 
temp0=get_keypad_input();        // getting  second digit in min
if(temp0=='y')
{
  LCD4bits_Cmd(0x01);
 goto label;
}
delay_ms(200); 
cursor_decrement(1);         // shifting cursor to the left
LCD4bits_Data(temp0);            //writing second digit in min  (00:0k)
temp1=get_keypad_input();    // getting second digit in min
       
  if(temp1=='y')
{
  LCD4bits_Cmd(0x01);
 goto label;
}
delay_ms(200);               
cursor_decrement(2);
LCD4bits_Data(temp0);
LCD4bits_Data(temp1);
temp2=get_keypad_input();
  if(temp2=='y')
{
  LCD4bits_Cmd(0x01);
 goto label;
}
delay_ms(200);
cursor_decrement(4);
LCD4bits_Data(temp0);
LCD4bits_Cmd(0x14);
LCD4bits_Data(temp1);
LCD4bits_Data(temp2);
temp3=get_keypad_input();
   if(temp3=='y')
{
  LCD4bits_Cmd(0x01);
 goto label;
}
delay_ms(200);
cursor_decrement(5);
LCD4bits_Data(temp0);
LCD4bits_Data(temp1);
LCD4bits_Cmd(0x14);
LCD4bits_Data(temp2);
LCD4bits_Data(temp3);
LCD4bits_Cmd(0x01);
while(!(GPIO_PORTF_DATA_R&0x01)==0);
timer((temp0-'0')*10 +(temp1-'0'),(temp2-'0')*10+(temp3-'0'));
 
  break;
  }
 }
 }
 }
