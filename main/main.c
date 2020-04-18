#include <c8051f020.h>
#include "std_macros.h"
#include "DIO.h"
#include "Keypad.h"
#include "SevenSegments.h"
#include "stepper.h"
#define NOTPRESSED 0xff

#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b);
void append(char *ar, char size, char ch);
void checkPresed(void);


unsigned char value,presed,step;
char sevensegmentValue;
char up[3] ={6,0,4}; // up falgs list
char down[3] ={1,5,7}; // down flags list
char buttonPresed[8] = {1,1,1,1,1,1,1,1};
char buttonPresedFlags[8] = {0,0,0,0,0,0,0,0};
char keypadFlags[5] = {0,1,2,3,4};
char keypadvalues[5] = {0};
char arr[4] = {0,1,2,3}; // sevenSegments number
// renames pins name
sbit oneUp = P3^0;
sbit oneDown = P3^1;
sbit twoUp = P3^4;
sbit twoDown = P3^5;
sbit zeroUp = P3^6;
sbit threeDown = P3^7;

//char UPlist[3] = {P3,0,0}; // list of upPins
//char DOWNlist[3] = {oneDown,twoDown,threeDown}; // list of downPins
volatile char count = 0;
volatile char flag = 0;
/*
void ext_int_0() interrupt 0
{ 
    count++;
}

void ext_int_1() interrupt 2
{ 
    count--;
}
*/
sbit LED = P0^0;
void timer0_isr() interrupt 1
{
	TH0 = 0X4B;        //ReLoad the timer value
    TL0 = 0XFD;
    count++;        // Toggle the LED pin 
		LED = !LED;
}

void main (void)
{
	WDTCN = 0xDE;
	WDTCN = 0xAD;
	keypad_vInit(1);
	DIO_setPort_OutPutMode(3,1);
	seven_seg_init(0,0);
	seven_seg_init(0,1);
	motor_init(2,0);
	motor_init(2,1);
	interrupt_enable();
	
	interrupt_1Enable();
	DIO_setPortInput(3);
	
	 CLR_BIT(CKCON,3); // 
	//set the timer mode 
	CLR_BIT(TMOD,1);
	CLR_BIT(TMOD,0);
	TL0 = 0x00; // start value
	TH0 = 0x00; //relaod value
	SET_BIT(IE,1);
	initTimer();
	//SET_BIT(TCON,4);
	
	

	while(1)
	{
		if(count >= 50)
		{
			motor_rotate(2,2,1);      // Toggle the LED pin 
			count = 0;
		}
		/*
		checkPresed();		
		step =0;
		presed = keypad_press(1);
		append(keypadvalues,sizeof(keypadvalues),presed);
		// printf("chArray (after append) : %s\n", keypadvalues);
	//	qsort(keypadvalues, 5, sizeof(char), cmpfunc);
		

		if(presed != NOTPRESSED)
		{
			for(step=0;step<5;step++)
			{
			seven_seg_write(0,keypadvalues[step],0);
			}
			/*
			motor_rotate(2,2,1);
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
			*/
			}
		

}

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
	
	void append(char *ar, char size, char ch) {
    char index = 0;
    // Get to the end of the string
    while (*ar) {
        ar++;
        ++index;
    }
 
    // If sufficient space, append
    // Otherwise, do nothing
    //
    if (index < size-1) {
        *ar = ch;
        *(ar+1) = '\0';
    }
}
	
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

	/*
		for(step=0;step<8;step++)
		{
			if(buttonPresedFlags[step]==1)
			{
				DIO_write(2,step,0);
				delay_ms(1);
			}
		}
		*/
		