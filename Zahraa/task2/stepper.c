#include <c8051f020.h>
#include <DIO.h>

void delay_ms(unsigned int k)
{
  unsigned int i,j;
     for(i=0;i<=k;i++)
	    for(j=0;j<110;j++);
}
unsigned char m;
signed char a;
unsigned char rot_angle[] = {0x06,0x03,0x09,0x0C};
void main()
{
   DIO_setPort_OutPutMode(2,0);
   

   
   
   while(1)
   {
	 //motor1
	  for(m = 0; m<4; m++){
	  
	     write_low_nibble(2,rot_angle[m]);
		 delay_ms(1000);}
	  
   	  
	  
	  
	  //motor 2
	  for(a = 3; a>=0;a--){
	  
	     write_high_nibble(2,rot_angle[a]);
		 delay_ms(1000);}
		 /*
	  write_high_nibble(2,0x06);
	  delay_ms(1000);
	  write_high_nibble(2,0x03);
	  delay_ms(1000);
	  write_high_nibble(2,0x09);
	  delay_ms(1000);
	  write_high_nibble(2,0x0c);
	  delay_ms(1000);
		 */
   }
}