#include <c8051f020.h>
#include <DIO.h>

signed char i;
unsigned char rot_angle[] = {0x06,0x03,0x09,0x0C};

void motor_init(unsigned char portname , unsigned char setPosition)
{
	if (setPosition == 0 )
	{
	DIO_setPin_OutPutMode(portname,0,1);
	DIO_setPin_OutPutMode(portname,1,1);
	DIO_setPin_OutPutMode(portname,2,1);
	DIO_setPin_OutPutMode(portname,3,1);
	}
	else
	{
	DIO_setPin_OutPutMode(portname,4,1);
	DIO_setPin_OutPutMode(portname,5,1);
	DIO_setPin_OutPutMode(portname,6,1);
	DIO_setPin_OutPutMode(portname,7,1);
	}
}

void motor_rotate(unsigned char portname , unsigned char setPosition,unsigned char direction)
	{
	  if(setPosition==0)
		{
			if(direction ==0)
				{
					for(i = 0; i<4; i++)
					{
					write_low_nibble(portname,rot_angle[i]);
					delay_ms(500);
					}
			}
			else
			{
				for(i = 3; i>=0;i--)
				{
				write_low_nibble(portname,rot_angle[i]);
				delay_ms(500);
				}
			}
		}
		else
		{
			if(direction ==0)
			{
				for(i = 0; i<4; i++)
				{
				write_high_nibble(portname,rot_angle[i]);
				delay_ms(500);
				}
			}
			else
			{
				for(i = 3; i>=0;i--)
				{
				write_high_nibble(portname,rot_angle[i]);
				delay_ms(500);
				}
			}
		}
}