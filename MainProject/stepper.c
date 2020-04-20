#include <c8051f020.h>
#include <DIO.h>

signed char i = 0;
signed char g = 3;
unsigned char rot_angle[] = {0x03,0x06,0x0C,0x09};

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
					for(i=0;i<=3;i++)
					{
					write_low_nibble(portname,rot_angle[i]);
					delay_ms(100);
					}
				}
			else
			{
				for(g=3;g>=0;g--)
				{
				write_low_nibble(portname,rot_angle[g]);
					delay_ms(100);
				}
			}
		}
		else
		{
			if(direction ==0)
			{
				for(i=0;i<=3;i++)
				{
				write_high_nibble(portname,rot_angle[i]);
					delay_ms(200);
				}
			}
			else
			{
				for(g=3;g>=0;g--)
				{
				write_high_nibble(portname,rot_angle[g]);
					delay_ms(200);
				}
				
				
			}
		}
}