#include "DIO.h"
#include "std_macros.h"
#include <c8051f020.h>


void seven_seg_init(unsigned char portname , unsigned char setPosition)
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
void seven_seg_write(unsigned char portname,unsigned char value ,unsigned char setPosition)
{
	if (setPosition == 0 )
	{
	write_low_nibble(portname,value);
	}
	else
	{
		write_high_nibble(portname,value);
	}
}