#include <display.h>
#include <serial.h>
#include <definition.h>
//|0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|
//|S|T|,|-|0|0|0|0|3|.|6|9| | |%|
bit sign=0;
void NT_10byte(void)
{
	signed char i,j,position;	
			if (uartbuffer[3] == '-')
				{sign=1;}
			else
				{sign=0;}
		for(i=4;i<0x0B;i++)
			{
				if ((uartbuffer[i] == '0')&&(uartbuffer[i+1] != '.'))
					{uartbuffer[i] =' '; }
				else
					{break;}
			}
				
		for (i=0x0B,j=0; j<=5; i--)
			{		
				if (uartbuffer[i] == '.')
					{position=0x0B-i;}
				else
					{displayRAM[5-j] = uartbuffer[i]; j++;}
			}

	for (i=0x0B,j=0;i>0x00;i--,j++)
		{
			if (uartbuffer[i] == '.')
			 {break;}
		}		
	switch(j)
		{
			case 1:dp1=1;break;
			case 2:dp2=1;break;
			case 3:dp3=1;break;
			case 4:dp4=1;break;
			case 5:dp5=1;break;
			default:dp1=0;dp2=0;dp3=0;dp4=0;dp5=0;
		}		
}