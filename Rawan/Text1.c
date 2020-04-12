#include <reg51.h>
sbit R0=P1^0;
sbit R1=P1^1;
sbit R2=P1^2;
sbit R3=P1^3;
sbit C0=P1^4;
sbit C1=P1^5;
sbit C2=P1^6;
void seg(unsigned int);

void main()
{
	R0=R1=R2=R3=1;
	R0=0;
	if(C0==0)
		seg(0xF9);
	
		R0=R1=R2=R3=1;
	R0=0;
	if(C1==0)
		seg(0xA4);
	
		R0=R1=R2=R3=1;
	R0=0;
	if(C2==0)
		seg(0xB0);
	
		R0=R1=R2=R3=1;
	R1=0;
	if(C0==0)
		seg(0x99);
	
		R0=R1=R2=R3=1;

}
void seg(unsigned int ch)
{
	P2=0x00;
	P2=ch;
}	