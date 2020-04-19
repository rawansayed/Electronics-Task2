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
unsigned char presed,step,buttonFlagPresed,opencounter;
char sevensegmentValue,elevator;

char open = false;
char close = false;
char up = false;
char down = false;
char buttonPresed[8] = {1,1,1,1,1,1,1,1};
char buttonPresedFlags[8] = {0,0,0,0,0,0,0,0};
char keypadFlags[5] = {0,1,2,3,4};
char keypadvalues[5] = {0};
char arr[4] = {0,1,2,3}; // sevenSegments number


volatile char count = 0;
volatile char count2 = 0;
/*
void ext_int_0() interrupt 0
{ 
    count = 0;
}
*/


void timer0_isr() interrupt 1
{
	TH0 = 0X4B;        //ReLoad the timer value
    TL0 = 0XFD;
    count++;        // Toggle the LED pin 
		count2++;
}

void main (void)
{
	sevensegmentValue = 0;
		seven_seg_write(0,sevensegmentValue,0);
	
	WDTCN = 0xDE;
	WDTCN = 0xAD;
	keypad_vInit(1);

	seven_seg_init(0,0);
	seven_seg_init(0,1);

	
	P3MDOUT &= 0x00;
	P3 = 0xff;
	
		TMOD = 0x01;       //Timer0 mode 1 
    TH0 = 0X4B;        //Load the timer value
    TL0 = 0XFD;
    TR0 = 1;           //turn ON Timer zero
    ET0 = 1;           //Enable TImer0 Interrupt
    EA = 1; 
   
	 DIO_setPin_OutPutMode(2,0,1);
	 DIO_setPin_OutPutMode(2,1,1);
	

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
							if(	down && buttonPresedFlags[1])
								{
								  open = true;
									buttonPresedFlags[4] = 0;
									down = false ;
								}
							else if ( !up && !down )
								{
									open=true;
								}
						}
					else
						{
							elevator = 0;
						}
				}
			
			if(buttonPresedFlags[1]==1)	
				{
					if (sevensegmentValue == 3)
						{

							if (up && buttonPresedFlags[1])
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
							elevator = 3;
						}
				}
				
			if(buttonPresedFlags[5]==1 || buttonPresedFlags[6]==1)	
				{
					if (sevensegmentValue == 2)
						{
							if(	down && buttonPresedFlags[5])
								{
									
									open = true;				
									buttonPresedFlags[5] = 0;
									down = false;
									
								}
							else if (up && buttonPresedFlags[6])
								{	
									open = true;
									buttonPresedFlags[6] = 0;
									up = false;
									
									
								}
							else if ( !up && !down )
								{
										open = true;
									
								}
						}
					else
						{
							elevator = 2;
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
				checkPresed();
			if(sevensegmentValue < elevator)
				{
					elevUP();
					up = true;
					checkPresed();
				}
			else if(sevensegmentValue > elevator)
				{
					elecvDOWN();
					down = true;
					checkPresed();
				}
			else
			{
				up = false;
				down = false;
			}

				
				
			
		
		if(count >= 50 && up)
			{
				sevensegmentValue++;
				seven_seg_write(0,sevensegmentValue,0);
				count = 0;
			}
		if(count >= 50 && down)
			{
				sevensegmentValue--;
				seven_seg_write(0,sevensegmentValue,0);
				count = 0;
			}
		if(count2 >= 30 && open)
			{
				motor_rotate(2,1,0);
				opencounter++;
				if(opencounter>=2)
				{
					opencounter =0;
					open = false;
				}
				
				count2 =0;
				
			}
		if(count2 >= 30 && close)
			{
				
				motor_rotate(2,1,0);
				count2 =0;
				opencounter++;
				if(opencounter==2)
				{
					opencounter =0;
					open = false;
				}
			}

			
	}
			
			
}
	}		
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
		