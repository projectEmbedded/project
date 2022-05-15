#include "tm4c123gh6pm.h"
unsigned char Switch2_input(void)
  {
   return GPIO_PORTF_DATA_R & 0x01;
  }  
  unsigned char Switch1_input(void)
  {
  return GPIO_PORTF_DATA_R & 0x10;
  }