#define RS 0x01				 	//RS (PB0) 
#define EN 0x04  		 	 	//EN (PB2)

#define lcd_clear 0x01
 

#include "tm4c123gh6pm.h"
#include "delays.h"

void LCD_Write4bits(unsigned char data, unsigned char control) //control is RS value 
{
	data &= 0xF0;                       //clear lower nibble for control 
	control &= 0x0F;                    //clear upper nibble for data
	GPIO_PORTB_DATA_R = data | control;         // oring RS value with data 
	GPIO_PORTB_DATA_R  = data | control | EN;    //pulse EN
	delay_micro(0);													//delay for pulsing EN
	GPIO_PORTB_DATA_R  = data | control;					//Turn off the pulse EN
	GPIO_PORTB_DATA_R  = 0;              //Clear the Data 
}

void LCD4bits_Data(unsigned char data)
{
	LCD_Write4bits(data & 0xF0 , RS);   //upper nibble first
	LCD_Write4bits(data << 4 , RS);     //then lower nibble
	delay_micro(40);												//delay for LCD (MCU is faster than LCD)
}

void LCD_WriteString(char * str)
{  
	volatile int i = 0;          //volatile is important 
	
	while(*(str+i) != '\0')       //until the end of the string
	{
		LCD4bits_Data(*(str+i));    
		i++;                        //increment for next character
	}
}

void LCD4bits_Cmd(unsigned char command)
{
	LCD_Write4bits(command & 0xF0 , 0);    //upper nibble first
	LCD_Write4bits(command << 4 , 0);			 //then lower nibble
	
	if(command < 4)
		delay_ms(2);       
	else
		delay_micro(40);      
}

void LCD4bits_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x02;    //enable clck for portb
	delay_ms(10);                 //delay 10 ms for enable the clock of PORTB
  GPIO_PORTB_DIR_R |= 0xFF;             // PORTB as output pins
  GPIO_PORTB_DEN_R |= 0xFF;           //digital enable for portb
	LCD4bits_Cmd(0x28);          //2 lines and 5x7 character (4-bit data, D4 to D7)
	LCD4bits_Cmd(0x06);          //Automatic Increment cursor (shift cursor to right)
	LCD4bits_Cmd(lcd_clear);					 //Clear display screen
	LCD4bits_Cmd(0x0F);          //Display on, cursor blinking
}

void cursor_decrement(int f)
{
 int g;
  for(g=0 ; g<f ; g++)
	{
     LCD4bits_Cmd(0x10);
  }
}
	


