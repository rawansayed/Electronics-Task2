#include <c8051f020.h>
#include "std_macros.h"
#include "DIO.h"
#include "Keypad.h"
#include "SevenSegments.h"
#include "stepper.h"
#define NOTPRESSED 0xff


unsigned char value,presed,step;
char sevensegmentValue;

char arr[4] = {0,1,2,3};

void main (void)
{
 
	keypad_vInit(1);
	DIO_setPort_OutPutMode(3,1);
	seven_seg_init(0,0);
	seven_seg_init(0,1);
	motor_init(2,0);
	motor_init(2,1);
	interrupt_enable();
	interrupt_0Enable();
	interrupt_1Enable();
	DIO_setPortInput(3);
	
	
	
	while(1)
	{
		step =0;
		presed = keypad_press(1);
		if(presed != NOTPRESSED)
		{
			sevensegmentValue = presed;
			while(sevensegmentValue != -1)
			{
				if(step!=sevensegmentValue)
				{
				seven_seg_write(0,arr[step],0);
				step++;
				}
				else{
				break;
				}
				motor_rotate(2,0,0);
				
				sevensegmentValue--;
			}
		
		
		}
		
		
		
	}
}