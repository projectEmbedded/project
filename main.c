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
char x, emp0,temp1,temp2,temp3;
int h;

 
 void idle(void)
{
        LCD_WriteString("close the door");
	while((GPIO_PORTA_DATA_R&0X08)==0);
	delay_milli(200);             // wait for 200 ms
	 LCD4bits_Cmd(0X01);           // clear lcd 
         spaces(4);                    // displays 4 spaces
	 LCD_WriteString("mode?"); 	// displays "mode?"
         x=get_keypad_input(); 		// get the input ( A,B,C,D)
         buzzer();			// function buzzer to make sound every time we prss on the keypad
         LCD4bits_Cmd(0x01);  		// clear lcd 
}
 
 
 
	int main (void)
{ int y,z,h,j;
	char k,temp1,temp2,temp3,n;
Leds_init();		
PortA_init();
PortC_init();
PortE_init();
PortB_init();
LCD4bits_Init();	
switches();
 
 
while(1)
 { 
	 start :                     // start label 
	 idle();                     // idle state 
	switch(x)                          
 {
	case ('A'):                               
 {
   spaces(3);                          // display 3 spaces
   LCD_WriteString("POPCORN");       //display popcorn
   while(!(GPIO_PORTF_DATA_R&0x01)==0 || (GPIO_PORTA_DATA_R&0X08)==0); // wait until switch2 is pressed while the door is closed
   delay_ms(1000);                // wait for 1 sec
   LCD4bits_Cmd(0x01);            // clear lcd
   timer(1,0);                    // display 1 minute and count down
   goto start;                   // go back to the start label
   break;
 }
	
 case('B'):
		{
		  spaces(2); 
		  LCD_WriteString("Beef weight?");	//ask for the beef weight 	
		  delay_ms(2000);			// delay for 2 seconds 
		  LCD4bits_Cmd(0x01);			// clear lcd 
                  delay_ms(1000);			// delay for 1 second 
     	          weight_beef();			// call the function (weight_beef()) to calculate the time and take th number of kilos
		  goto start;				// back to label start 
		 break;
		}

  case ('C'):
{ 

	 LCD_WriteString("Chicken weight?");		//ask for the Chicken weight
	 delay_ms(2000);				// delay for 2 seconds
         LCD4bits_Cmd(0x01);				// clear lcd 
         delay_ms(1000);				// delay for 1 second
         weight_chicken();				// call the function (weight_chicken()) to calculate the time and take th number of kilos
         goto start;					// back to label start
	 break;
}
		
  case ('D'):
  {  
	
	LCD_WriteString("Cooking Time?");		//ask for the Cooking Time
        delay_ms(2000);					// delay for 2 seconds	
	LCD4bits_Cmd(0X01);				// clear lcd 
	user_input :					// call the function (user_input) to take the time which the user want	
	LCD_WriteString("maximum 30 min");		// the maximum time is 30 minute
	LCD4bits_Cmd(0xc0);			
	LCD_WriteString("minimum 1 second");		// the minimum time is 1 second 
	delay_ms(2000);					// delay for 2 seconds
	LCD4bits_Cmd(0x01);				// clear lcd 
  Again :
        spaces(4); // printing 4 spaces to center the count time
	  LCD_WriteString("00:00");       // writing (00:00) on lcd  
          temp0=get_keypad_input();       // getting  second digit in min (tens)
          buzzer();                       //the buzzer produces an audible tone while pressing on the keypad
        if(temp0=='y')                  // checking if switch1 is pressed
    {
      LCD4bits_Cmd(0x01);         //  if pressed then clear the lcd 
      goto Again;                 // then goto idle and wait for a new input
   }
    delay_ms(200);               // wait for 200 milliseconds
    cursor_decrement(1);         // shifting cursor to the left
    LCD4bits_Data(temp0);        //displaying second digit in min  
    temp1=get_keypad_input();    // getting  first digit in min (units)
    buzzer();                  //the buzzer produces an audible tone while pressing on the keypad
    if(temp1=='y')              // checking if switch1 is pressed
   {          
    LCD4bits_Cmd(0x01);        // if pressed then clear the lcd 
    goto Again;                 // then goto idle and wait for a new input
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
   goto Again;                   // then goto idle and wait for a new input
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
  goto Again;                    // then goto idle and wait for a new input
  }
delay_ms(200);                    // wait for 200 milliseconds
cursor_decrement(5);               // shifting the cursor 5 spaces to the left
LCD4bits_Data(temp0);             // displaying second digit in min
LCD4bits_Data(temp1);             // displaying first digit in min
LCD4bits_Cmd(0x14);                // shifting cursor to the right
LCD4bits_Data(temp2);              // displaying second digit in second 
LCD4bits_Data(temp3);               // displaying first digit in second
LCD4bits_Cmd(0x01);                 // clear the lcd
if(temp0>=('3') && temp1>=('0')&& temp2>=('0') && temp3>=('0'))   //check if time input is >30 min 
{
   goto user_input;                                              // if true  then goto userinput again
}
if(temp0==('0') && temp1==('0')&& temp2==('0') && temp3<('1'))  // check if time input <1 sec 
{
	goto user_input;                                        //then goto userinput again
}
while(!(GPIO_PORTF_DATA_R&0x01)==0 || (GPIO_PORTA_DATA_R&0X08)==0); // wait until switch2 is pressed while the door is closed
timer((temp0-'0')*10 +(temp1-'0'),(temp2-'0')*10+(temp3-'0')); 
 goto start;
  break;
  }
 }
 }
 }
