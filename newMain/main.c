#include <c8051f020.h>
#include "std_macros.h"
#include "DIO.h"
#include "Keypad.h"
#include "SevenSegments.h"
#include "stepper.h"
#define NOTPRESSED 0xff
#define true 1
#define false 0

void checkPresed(void);


void elevUP(void);
void elecvDOWN(void);
void elevSTOP(void);
unsigned char presed,step,buttonFlagPresed;
char sevensegmentValue,elevator;
char opencounter=0;
char upvalue = 0;
char downvalue = 0;
char wait;
char open = false;
char close = false;
char up = false;
char down = false;
char buttonPresed[8] = {1,1,1,1,1,1,1,1};
char buttonPresedFlags[8] = {0,0,0,0,0,0,0,0};
char keypadFlags[5] = {0,1,2,3,4};
char keypadvalues[5] = {0};
char arr[4] = {0,1,2,3}; // sevenSegments number

sbit led = P0^0;
volatile char count = 0;
volatile char count2 = 0;
/*
void ext_int_0() interrupt 0
{ 
    count = 0;
}
*/


void timer1_isr() interrupt 3
{
	TH1 = 0X4B;        //Load the timer value
    TL1 = 0XFD;
	wait++;
	up = false;
				down= false;
}
void timer0_isr() interrupt 1
{
	TH0 = 0X4B;        //ReLoad the timer value
    TL0 = 0XFD;
    count++;        // Toggle the LED pin 
		count2++;
}

void main (void)
{
	
	
		WDTCN = 0xDE;
		WDTCN = 0xAD;
		keypad_vInit(1);

		seven_seg_init(0,0);
		seven_seg_init(0,1);
		sevensegmentValue = 0;
		seven_seg_write(0,sevensegmentValue,0);
		
		P3MDOUT &= 0x00;
		P3 = 0xff;
	
		TMOD = 0x01;       //Timer0 mode 1 
		SET_BIT(TMOD,4);
		TH1 = 0X4B;        //Load the timer value
    TL1 = 0XFD;
    TH0 = 0X4B;        //Load the timer value
    TL0 = 0XFD;
    TR0 = 1;           //turn ON Timer zero
		TR1 = 1;
    ET0 = 1;           //Enable TImer0 Interrupt
		
    EA = 1; 
   
	 //DIO_setPin_OutPutMode(2,0,1);
	 //DIO_setPin_OutPutMode(2,1,1);
	

	while(1)
	{

		checkPresed();
		for(step=0;step<8;step++)
			{
				if (buttonPresedFlags[step] == 1) 
				{
					buttonFlagPresed = 1;
				}
			}
		while(buttonFlagPresed)
	{
		
			if(buttonPresedFlags[0]==1 )	
				{
					if (sevensegmentValue == 0)
						{
							if(down)
								{
									down = false ;
								}
									open=true;
									buttonPresedFlags[0] = 0;
						}
					else
						{
							elevator = 0;
						}
				}
			if(buttonPresedFlags[3]==1 || buttonPresedFlags[4]==1)	
				{
					if (sevensegmentValue == 1)
						{
							if(	down && buttonPresedFlags[4])
								{
									open=true;
									buttonPresedFlags[4] = 0;
									down = false;
									
								}
							else if (up && buttonPresedFlags[3])
								{	
									open=true;
									buttonPresedFlags[3] = 0;
									up = false;
								}
							else if ( !up && !down )
								{
									open=true;
								}
						}
					else
						{
							elevator = 1;
						}
				}
				if(buttonPresedFlags[5]==1 || buttonPresedFlags[6]==1)	
				{
					if (sevensegmentValue == 2)
						{
							if(	down && buttonPresedFlags[6])
								{						
									buttonPresedFlags[6] = 0;
									down = false;
									open = true;	
									
								}
							else if (up && buttonPresedFlags[5])
								{	
									buttonPresedFlags[5] = 0;
									open = true;
									up = false;
								}
							else
							{
								open = true;
							}
						}
					else
						{
							elevator = 2;
						}
				}
				if(buttonPresedFlags[1]==1)	
				{
					if (sevensegmentValue == 3)
						{
							if (up)
								{	
									up = false;
								}
								open=true;
								buttonPresedFlags[1] = 0;
						}
					else
						{
							elevator = 3;
						}
				}
				checkPresed();
			if(sevensegmentValue < elevator)
				{
					up = true;
				}
			else if(sevensegmentValue > elevator)
				{
					down = true;
				}
			else
			{
				up = false;
				down = false;
			}
		
			
				if(open)
			{		
				motor_rotate(2,1,0);
				open=false;
				up = false;
				down= false;
				ET1= 1;
			}
			if(close)
			{
				motor_rotate(2,1,1);
				close = false;
				up = false;
				down= false;
			}
			if(wait >= 40)
			{
				close = true;
				ET1= 0;
				wait = 0;
				up = false;
				down= false;
			}		
		if(count >= 20 && up)
			{
				if(upvalue >= 3)
					{
						sevensegmentValue++;
						seven_seg_write(0,sevensegmentValue,0);
						upvalue = 0;
					}
					upvalue++;
					motor_rotate(2,0,0);
						count =0;		
			}
			
		if(count >= 20 && down)
			{
				if(downvalue >= 3)
					{
						sevensegmentValue--;
						seven_seg_write(0,sevensegmentValue,0);
						downvalue = 0;
					}
					downvalue++;
					motor_rotate(2,0,1);
					count =0;
			}

	}
		
}
	}	
/*
void elevUP(void)
{
	if(count2 >= 30)
	{
		motor_rotate(2,0,0);
		count2 =0;
	}
}
void elecvDOWN(void)
{
	if(count2 >= 30)
	{
		motor_rotate(2,0,1);
		count2 =0;
	}
}
*/
/*
void open(void)
{
	if(count2 >= 30)
	{
		motor_rotate(2,1,1);
		count2 =0;
	}
}	
void close(void)
{
	count3 = 0;
	if (count3 <=50)
	{
		if(count2 >= 30)
		{
			motor_rotate(2,1,0);
			count2 =0;
		}
	}
}
*/

	
/*
void elevUP(void)
{
	SET_BIT(P2,0);
	CLR_BIT(P2,1);
}
void elecvDOWN(void)
{
	CLR_BIT(P2,0);
	SET_BIT(P2,1);
}
void elevSTOP(void)
{
	DIO_write(2,0,1);
	DIO_write(2,1,1);
}
void open(void)
{
	SET_BIT(P2,4);
	CLR_BIT(P2,5);
}	
void close(void)
{
	CLR_BIT(P2,4);
	SET_BIT(P2,5);
}	
void stop(void)
{
CLR_BIT(P2,5);
	CLR_BIT(P2,4);
}
*/

void checkPresed(void)
	{
		for(step=0;step<8;step++)
		{
			buttonPresed[step]=DIO_read(3,step);
			delay_ms(1);
		}
		for(step=0;step<8;step++)
		{
			if(0 == buttonPresed[step])
			{
				buttonPresedFlags[step] = 1;
			}
		}
	}
		