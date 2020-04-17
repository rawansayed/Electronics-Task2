#include <c8051f020.h>
#include "std_macros.h"
#include "DIO.h"
#include "Keypad.h"
#include "SevenSegments.h"
#include "stepper.h"
#define NOTPRESSED 0xff


unsigned char value,presed;

void main (void)
{

keypad_vInit(1);
	DIO_setPort_OutPutMode(3,1);
	seven_seg_init(0,0);
	seven_seg_init(0,1);
	motor_init(2,0);
	motor_init(2,1);
	
	
	while(1)
	{
	value = keypad_u8check_press(1);
	if (value != NOTPRESSED)
	{
		if (!(value==11 || value==12 ))
		{
		seven_seg_write(0,value,0);
			delay_ms(1000);
		}
		else
		{
			if (value==11)
			{
				presed++;
				seven_seg_write(0,presed,1);
				delay_ms(1000);
			}
			else
			{
				presed--;
				seven_seg_write(0,presed,1);
				delay_ms(1000);
			}
		}
	
	
	}
	if (value ==1)
	{
	motor_rotate(2,0,0);
		motor_rotate(2,1,1);
	}
	if (value ==2)
	{
	motor_rotate(2,0,1);
		motor_rotate(2,1,0);
	}
	
	}
}