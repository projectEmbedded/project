#include "tm4c123gh6pm.h"


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
void delay_ms(int num) 
{
int i; 
for(i=0; i<num; i++)
{
SysTick_Wait1ms();
}
}
