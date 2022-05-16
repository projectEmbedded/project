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
#include "weight_functions.h"
char temp0,temp1,temp2,temp3;
int h;

 
 void idle(void)
{
  
	while((GPIO_PORTA_DATA_R&0X08)==0);
	 
}
 
 
	int main (void)
{ int y,z,h,j;
	char x,k,temp1,temp2,temp3,n;
Leds_init();
PortA_init();
PortC_init();
PortE_init();
PortB_init();
LCD4bits_Init();	
switches();
 
 
	while(1)
 { 
	 start :
	 idle();
	 delay_milli(200);
	 LCD_WriteString("mode?");
   x=get_keypad_input();
   buzzer();	 
	 LCD4bits_Cmd(0x01);
	 switch(x)
 {
	case ('A'):                              
 {
  for(j=0;j<3;j++)
		{ 
			LCD4bits_Data(' ');
		}
	 LCD_WriteString("POPCORN");
   while(!(GPIO_PORTF_DATA_R&0x01)==0 && !switch3_input()==0);
   delay_ms(1000);
   LCD4bits_Cmd(0x01);
   timer(1,0);
  goto start;
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
		goto start;
			break;
		}

   case ('C'):
{ 

	LCD_WriteString("Chicken weight?");
	 delay_milli(2000);
   LCD4bits_Cmd(0x01);
   delay_ms(1000);
   weight_chicken();
 goto start;
			break;
}
		
		case ('D'):
  {  
	
	LCD_WriteString("Cooking Time?");
  delay_ms(2000);
	LCD4bits_Cmd(0X01);
	user_input :
	LCD_WriteString("maximum 30 min");
	delay_ms(2000);
	LCD4bits_Cmd(0x01);
	for(h=0 ; h<4 ; h++)
{
    LCD4bits_Data(' ');      // printing 4 spaces
}
LCD_WriteString("00:00");    // writing (00:00) on lcd   00:01 >> 30:00 
temp0=get_keypad_input();        // getting  second digit in min
buzzer();
if(temp0=='y')
{
  LCD4bits_Cmd(0x01);
 goto start;
}
delay_ms(200); 
cursor_decrement(1);         // shifting cursor to the left
LCD4bits_Data(temp0);            //writing second digit in min  (00:0k)
temp1=get_keypad_input();    // getting second digit in min
  buzzer();     
  if(temp1=='y')
{
  LCD4bits_Cmd(0x01);
 goto start;
}
delay_ms(200);               
cursor_decrement(2);
LCD4bits_Data(temp0);
LCD4bits_Data(temp1);
temp2=get_keypad_input();
buzzer(); 
if(temp2=='y')
{
  LCD4bits_Cmd(0x01);
 goto start;
}
delay_ms(200);
cursor_decrement(4);
LCD4bits_Data(temp0);
LCD4bits_Cmd(0x14);
LCD4bits_Data(temp1);
LCD4bits_Data(temp2);
temp3=get_keypad_input();
buzzer();  
if(temp3=='y')
{
  LCD4bits_Cmd(0x01);
 goto start;
}
delay_ms(200);
cursor_decrement(5);
LCD4bits_Data(temp0);
LCD4bits_Data(temp1);
LCD4bits_Cmd(0x14);
LCD4bits_Data(temp2);
LCD4bits_Data(temp3);
LCD4bits_Cmd(0x01);
if((temp0==(3+'0')) && (temp1>(0+'0')))
{
   goto user_input;
}
while(!(GPIO_PORTF_DATA_R&0x01)==0);
timer((temp0-'0')*10 +(temp1-'0'),(temp2-'0')*10+(temp3-'0'));
 goto start;
  break;
  }
 }
 }
 }
