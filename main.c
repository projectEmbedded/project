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
   while(!(GPIO_PORTF_DATA_R&0x01)==0 || (GPIO_PORTA_DATA_R&0X08)==0);
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
	LCD4bits_Cmd(0xc0);
	LCD_WriteString("minimum 1 second");
	delay_ms(2000);
	LCD4bits_Cmd(0x01);
	for(h=0 ; h<4 ; h++)
{
    LCD4bits_Data(' ');          // printing 4 spaces to center the count time
}
LCD_WriteString("00:00");       // writing (00:00) on lcd  
temp0=get_keypad_input();       // getting  second digit in min (tens)
buzzer();                       //the buzzer produces an audible tone while pressing on the keypad
if(temp0=='y')                  // checking if switch1 is pressed
{
 LCD4bits_Cmd(0x01);         //  if pressed then clear the lcd 
 goto start;                  // then goto idle and wait for a new input
}
delay_ms(200);               // wait for 200 milliseconds
cursor_decrement(1);         // shifting cursor to the left
LCD4bits_Data(temp0);        //displaying second digit in min  
temp1=get_keypad_input();    // getting  first digit in min (units)
 buzzer();                  //the buzzer produces an audible tone while pressing on the keypad
  if(temp1=='y')              // checking if switch1 is pressed
 {          
  LCD4bits_Cmd(0x01);        // if pressed then clear the lcd 
  goto start;                 // then goto idle and wait for a new input
 }
delay_ms(200);                // wait for 200 milliseconds
cursor_decrement(2);          // shifting the cursor 2 spaces to the left
LCD4bits_Data(temp0);         // displaying second digit in min
LCD4bits_Data(temp1);         // displaying first digit in min
temp2=get_keypad_input();     // getting second digit in second (tens)
buzzer();                     //the buzzer produces an audible tone while pressing on the keypad
if(temp2=='y')                // checking if switch1 is pressed
{
  LCD4bits_Cmd(0x01);         // if pressed then clear the lcd 
 goto start;                   // then goto idle and wait for a new input
} 
delay_ms(200);                // wait for 200 milliseconds
cursor_decrement(4);           // shifting the cursor 4 spaces to the left
LCD4bits_Data(temp0);        // displaying second digit in min
LCD4bits_Cmd(0x14);          // shifting cursor to the right
LCD4bits_Data(temp1);        // displaying first digit in min
LCD4bits_Data(temp2);         // displaying second digit in second
temp3=get_keypad_input();      // getting first digit in second (units)
buzzer();                       //the buzzer produces an audible tone while pressing on the keypad 
if(temp3=='y')                   // checking if switch1 is pressed
{
  LCD4bits_Cmd(0x01);            // if pressed then clear the lcd 
 goto start;                     // then goto idle and wait for a new input
}
delay_ms(200);                    // wait for 200 milliseconds
cursor_decrement(5);               // shifting the cursor 5 spaces to the left
LCD4bits_Data(temp0);             // displaying second digit in min
LCD4bits_Data(temp1);             // displaying first digit in min
LCD4bits_Cmd(0x14);                // shifting cursor to the right
LCD4bits_Data(temp2);              // displaying second digit in second 
LCD4bits_Data(temp3);               // displaying first digit in second
LCD4bits_Cmd(0x01);                 // clear the lcd
if((temp0>=(3+'0')) && (temp1>=(0+'0'))&& (temp2>=(0+'0')) && (temp3>=0+'0')) goto user_input; // check if time input is >30 min then goto userinput again
 if((temp0=(0+'0')) && (temp1=(0+'0'))&& (temp2=(0+'0')) && (temp3<(1+'0'))) goto user_input; // check if time input is <1 second then goto userinput again
while(!(GPIO_PORTF_DATA_R&0x01)==0 || (GPIO_PORTA_DATA_R&0X08)==0); // wait until switch2 is pressed while the door is closed
timer((temp0-'0')*10 +(temp1-'0'),(temp2-'0')*10+(temp3-'0')); 
 goto start;
  break;
  }
 }
 }
 }
