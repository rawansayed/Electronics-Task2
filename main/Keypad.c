#include <REG51.h>
#include "std_macros.h"
#include <DIO.h>
#define NOTPRESSED 0xff
 void keypad_vInit(unsigned char portname)
 {
	 DIO_setPin_OutPutMode(portname,0,1);
	 DIO_setPin_OutPutMode(portname,1,1);
	 DIO_setPin_OutPutMode(portname,2,1);
	 DIO_setPin_OutPutMode(portname,3,1);
	 DIO_setInput(portname,4,0);
	 DIO_setInput(portname,5,0);
	 DIO_setInput(portname,6,0);
	 

	  
 }
 char keypad_press(unsigned char portname)
 {
	 unsigned char arr[4][3]={{1, 2, 3}
                            ,{4, 5, 6}
                            ,{7, 8, 9}
                            ,{11, 0, 12}};
	 char row,coloumn,x;
	 char returnval=NOTPRESSED;
	 for(row=0;row<4;row++)
	 {
		DIO_write(portname,0,1);
		DIO_write(portname,1,1);
		DIO_write(portname,2,1);
		DIO_write(portname,3,1);
		DIO_write(portname,row,0);
	
		for(coloumn=0;coloumn<3;coloumn++)
		{
			x=DIO_read(portname,(coloumn+4));
			if(x==0)
			 {
				 returnval=arr[row][coloumn];
				 break;
			 }  
		}	
		if(x==0)
		{
			break;
		}
	}	 
	 return returnval;	 
 }