

#include <c8051f020.h>
#include "std_macros.h"



void DIO_setPin_OutPutMode(unsigned char portname,unsigned char pinnumber,unsigned char direction)
{
		switch(portname)
	{
			case 0:
			if(direction==1)
			{
				SET_BIT(P0MDOUT,pinnumber);//Set the output mode of port0 to Push-Pull mode
			}
			else
			{
				CLR_BIT(P0MDOUT,pinnumber);//Set the output mode of port0 to Open-Drain mode
			}
		  break;

		case 1:
			if(direction==1)
			{
				SET_BIT(P1MDOUT,pinnumber);//Set the output mode of port0 to Push-Pull mode
			}
			else
			{
				CLR_BIT(P1MDOUT,pinnumber);//Set the output mode of port0 to Open-Drain mode
			}
			break;

		case 2:
			if(direction==1)
			{
				SET_BIT(P2MDOUT,pinnumber);//Set the output mode of port0 to Push-Pull mode
			}
			else
			{
				CLR_BIT(P2MDOUT,pinnumber);//Set the output mode of port0 to Open-Drain mode
			}
			break;
			
		case 3:
			if(direction==1)
			{
				SET_BIT(P3MDOUT,pinnumber);//Set the output mode of port0 to Push-Pull mode
			}
			else
			{
				CLR_BIT(P3MDOUT,pinnumber);//Set the output mode of port0 to Open-Drain mode
			}
			break;
		default: 
		break;

}
	}

void DIO_write(unsigned char portname,unsigned char pinnumber,unsigned char outputvalue)
{
	switch(portname)
	{
		case 0:
			if(outputvalue==1)
			{
				SET_BIT(P0,pinnumber);//Set the value of the given pin in port0 as High
			}
			else
			{
				CLR_BIT(P0,pinnumber);//Set the value of the given pin in port0 as Low
			}
			break ;
		
		case 1:
			if(outputvalue==1)
			{
				SET_BIT(P1,pinnumber);//Set the value of the given pin in port1 as High
			}
			else
			{
				CLR_BIT(P1,pinnumber);//Set the value of the given pin in port1 as Low
			}
			break ;
		
		case 2 :		
			if(outputvalue==1)
			{
				SET_BIT(P2,pinnumber);//Set the value of the given pin in port2 as High
			}
			else
			{
				CLR_BIT(P2,pinnumber);//Set the value of the given pin in port2 as Low
			}
			break ;
		
		case 3:
			if(outputvalue==1)
			{
				SET_BIT(P3,pinnumber);//Set the value of the given pin in port3 as High
			}
			else
			{
				CLR_BIT(P3,pinnumber);//Set the value of the given pin in port3 as Low
			}
			break ;
		default: break ;
	}
}

void DIO_setInput(unsigned char portname,unsigned char pinnumber,unsigned char direction)
{
	switch(portname)
		{
		case 0:
			// make the pin as input pin
			CLR_BIT(P0MDOUT,pinnumber);//Set the output mode of pinNumber of port0 to Open-Drain mode
			SET_BIT(P0,pinnumber); //Set the value of the given pin in port0 as High
			break;

		case 1:	
			// make the pin as input pin
			CLR_BIT(P1MDOUT,pinnumber);//Set the output mode of pinNumber of port1 to Open-Drain mode
			SET_BIT(P1,pinnumber); //Set the value of the given pin in port1 as High
			if(direction==1)
			{
				SET_BIT(P1MDIN,pinnumber); //Pin is configured in Analog Input mode.
			}
			else
			{
				 CLR_BIT(P1MDIN,pinnumber); //Pin is configured in Analog Input mode.
			}
			break;
		case 2:
			// make the pin as input pin
			CLR_BIT(P2MDOUT,pinnumber);//Set the output mode of pinNumber of port2 to Open-Drain mode
			SET_BIT(P2,pinnumber); //Set the value of the given pin in port2 as High
			break;
			
		case 3:
			// make the pin as input pin
			CLR_BIT(P3MDOUT,pinnumber);//Set the output mode of pinNumber of port3 to Open-Drain mode
			SET_BIT(P3,pinnumber); //Set the value of the given pin in port3 as High
			break;
		
	}
	
}


void DIO_toggle(unsigned char portname,unsigned char pinnumber)
{
	switch(portname)
	{
		case 0:
			TOG_BIT(P0,pinnumber);//Toggle the value of the given pin in port A
			break;
		
		case 1:
			TOG_BIT(P1,pinnumber);//Toggle the value of the given pin in port B
			break;
		
		case 2:
			TOG_BIT(P2,pinnumber);//Toggle the value of the given pin in port C
			break;
		
		case 3:
			TOG_BIT(P3,pinnumber);//Toggle the value of the given pin in port D
			break;
		
		default: break;
	}
}

unsigned char DIO_read(unsigned char portname,unsigned char pinnumber)
{
	unsigned char return_value=0;
	switch(portname)
	{
		case 0 :
		return_value=READ_BIT(P0,pinnumber);//Read the value from the given pin in port A
		break;
		
		case 1 :
		return_value=READ_BIT(P1,pinnumber);//Read the value from the given pin in port B
		break;
		
		case 2:
		return_value=READ_BIT(P2,pinnumber);//Read the value from the given pin in port C
		break;
		
		case 3 :
		return_value=READ_BIT(P3,pinnumber);//Read the value from the given pin in port D
		break;
		default: 
		break;
	}
	return return_value ;
}


void DIO_setPort_OutPutMode(unsigned char portname,unsigned char direction)
{
	switch(portname)
	{
		case 0:
		if(direction==1)
		{
			P0MDOUT |= 0xff;//Set the output mode of port0 to Push-Pull mode
		}
		else
		{
			P0MDOUT &= 0x00;//Set the output mode of port0 to Open-Drain mode
		}
		break;
		case 1:
		if(direction==1)
		{
			P1MDOUT |= 0xff;//Set the output mode of port1 to Push-Pull mode
		}
		else
		{
			P1MDOUT &= 0x00;//Set the output mode of port1 to Open-Drain mode
		}
		break;
		case 2:
		if(direction==1)
		{
			P2MDOUT |= 0xff;//Set the output mode of port2 to Push-Pull mode
		}
		else
		{
			P2MDOUT &= 0x00;//Set the output mode of port2 to Open-Drain mode
		}
		break;
		case 3:
		if(direction==1)
		{
			P3MDOUT |= 0xff;//Set the output mode of port3 to Push-Pull mode
		}
		else
		{
			P3MDOUT &= 0x00;//Set the output mode of port3 to Open-Drain mode
		}
		break;
		default: 
		break;
	}
	
}

void DIO_write_port(unsigned char portname,unsigned char portvalue)
{
	switch(portname)
	{
		case 0 :
			P0 = portvalue; //Write the given value to the port A
			break ;
		
		case 1:
			P1 = portvalue; //Write the given value to the port B
			break ;
		
		case 2 :
			P2 = portvalue; //Write the given value to the port C
			break ;
		
		case 3:
			P3 = portvalue; //Write the given value to the port D
			break ;
		
		default:
		 break ;
	}
}

unsigned char DIO_read_port(unsigned char portname)
{
	unsigned char return_val=0;
	switch(portname)
	{
		case 0 :
		return_val=P0; // read the value of port A 
		break ;
		case 1:
		return_val=P1; // read the value of port B 
		break ;
		case 2 :
		return_val=P2; // read the value of port C 
		break ;
		case 3:
		return_val=P3; // read the value of port D 
		break ;
		default:
		break ;
	}
	return return_val;
}





