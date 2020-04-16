#include <REG51.h>
#include <stdio.h>
#include <DIO.h>
unsigned char Keypad[4][3]={1, 2, 3,
                            4, 5, 6,
                            7, 8, 9,
                            0, 0, 0};

void main()
{
unsigned int x;
unsigned char a,b =0;
int j = 0;

while(1)
{
P1=0xFE;
x=P1;
if(x == 0xEE | x == 0xDE | x == 0xBE | x == 0x7E)
{
        if(x == 0xEE)
        {
                a = Keypad[0][0];
                P0 = a|(b<<4) ;
        }
        else if(x==0xDE)
        {
                a = Keypad[0][1];
                P0 = a|(b<<4);
        }
        else if(x==0xBE)
        {
                a = Keypad[0][2];
                P0 = a|(b<<4);
        }
}


P1 = 0xFD;
x = P1;
if(x == 0xED | x==0xDD | x==0xBD | x==0x7D)
{
        if (x==0xED)
        {
                a = Keypad[1][0]; 
				P0 = a|(b<<4);
        }
        else if(x==0xDD)
        {		
				a = Keypad[1][1];
                P0 = a|(b<<4) ;
        }
        else if (x==0xBD)
        {
				a = Keypad[1][2];
                P0 = a|(b<<4);
        }
}


P1 = 0xFB;
x=P1;
if(x == 0xEB | x ==0xDB | x == 0xBB | x == 0x7B)
{
        if (x==0xEB)
        {

				a = Keypad[2][0];
                P0 = a|(b<<4);
        }
        else if(x==0xDB)
        {
                a = Keypad[2][1];
				P0 = a|(b<<4) ;
        }
        else if(x==0xBB)
        {
                a = Keypad[2][2];
				P0 = a|(b<<4);
        }
}



P1=0xF7;
x=P1;
if(x == 0xE7 | x == 0xD7 | x == 0xB7)
{
        if (x==0xE7)
        {
		        if (b<=4)
				{
                b += 0x01;
                P0 = a|(b<<4); 
                for(j = 0; j<20000; j++);
				}
				
        }
        else if (x==0xD7)
        {
                a = Keypad[3][1];
				P0= a|(b<<4);
        }
        else if (x==0xB7)
        {
                P0=(Keypad[3][2]);
        }
}

}
}