#include "tm4c123gh6pm.h"
#include "switches_inputs.h"
#include "switches_inputs.h"
//extra delay functions
void delay_milli(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3180;j++)
{}
}
 
void delay_micro(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3;j++)
{}
}

//systick timer delays functions : 

void SysTick_Wait(unsigned long delay)  
{ 
NVIC_ST_CTRL_R = 0X00;
NVIC_ST_RELOAD_R = delay-1;
NVIC_ST_CURRENT_R = 0;
NVIC_ST_CTRL_R = 0X05;
while((NVIC_ST_CTRL_R&0x00010000)==0);
}

void SysTick_Wait1ms()
{
SysTick_Wait(16000);
}
void SysTick_Wait50ms()
{ 
  SysTick_Wait(800000);
}

	void delay_ms(int num) 
{
int i; 
for(i=0; i<num; i++)
{
SysTick_Wait1ms();
}
}

int  delay_mil() 
{
int i,h; 

	for(i=0; i<20; i++)
{ if( (Switch1_input()==0) ||(switch3_input()==0))  
	{
	
		h=pause(); 
	   if(h==1) return 1;  
	
	}
	SysTick_Wait50ms();
}
}

