#include <c8051f020.h>

void delay_ms(unsigned int k)
{
  unsigned int i,j;
     for(i=0;i<=k;i++)
	    for(j=0;j<110;j++);
}

void main()
{
   P2=0x00;
   while(1)
   {
      P2=0x06;
	  delay_ms(1000);
	  P2=0x03;
	  delay_ms(1000);
	  P2=0x09;
	  delay_ms(1000);
	  P2=0x0c;
	  delay_ms(1000);

   }
}