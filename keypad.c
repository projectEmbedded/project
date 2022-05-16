#include "tm4c123gh6pm.h"
#include "delays.h"
#include "switches_inputs.h"
unsigned char symbol[4][4] ={{'1', '2' ,'3', 'A'},{'4', '5', '6', 'B'},{'7', '8', '9', 'C'},{'*', '0', '#', 'D'}};

char get_keypad_input(void)
	{
	int i,j;
	
	
	while(1)
		{
  	if(Switch1_input() == 0) return 'y';                                        
			for( i = 0; i < 4; i++)                        //columns    
      {GPIO_PORTC_DATA_R = (1 << (i+4));
      delay_micro(2);
      for( j = 0; j < 4; j++)                     //rows 
      {
        if((GPIO_PORTE_DATA_R &0x0F )& (1 << j))
          return symbol[j][i];
      }
    }

	}
}
