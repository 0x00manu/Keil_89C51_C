#include <reg51.h>
#include <definition.h>
bit dp1=0,dp2=0,dp3=0,dp4=0,dp5=0;
//===========================================================
unsigned char displayRAM[6];//{"LSB 1 2 3 4 MSB"}
//===========================================================
extern code unsigned char table[];
extern bit sign;
void turnoff (void)
{
	transistor0 = 0;
	transistor1 = 0;
	transistor2 = 0;
	transistor3 = 0;
	transistor4 = 0;
	transistor5 = 0;
}
void ClearDisplay(void)
	{
		unsigned char i;
		for (i=0;i<6;i++)
		displayRAM[i] = ' ';
		dp1=0,dp2=0,dp3=0,dp4=0,dp5=0;
	}

void PushInSegments(unsigned char value)
	{ 
		unsigned char temp;
		temp = table [value];
		if ((temp & 0x01))
			{a = 1;}
		else
			{a = 0;}
		if ((temp & 0x02))
			{b = 1;}
		else
			{b = 0;}			
		if ((temp & 0x04))
			{c = 1;}
		else
			{c = 0;}			
		if ((temp & 0x08))
			{d = 1;}
		else
			{d = 0;}			
		if ((temp & 0x10))
			{e = 1;}
		else
			{e = 0;}			
		if ((temp & 0x20))
			{f = 1;}
		else
			{f = 0;}			
		if ((temp & 0x40))
			{g = 1;}				
		else
			{g = 0;}	
	}
	
void internaldisplay(void)
{
	static unsigned char counter = 0;
	unsigned char temp;
	temp = displayRAM[counter];
	PushInSegments(temp);
	h=1;
	switch(counter)				
		{											
			case 5:	transistor0	=	1;							
							break;//
			case 4:	transistor1	=	1;							
							if (dp1==1)
							{h=0;}
							break;//
			case 3:	transistor2	=	1;
							if (dp2==1)
							{h=0;}
							break;//
			case 2:	
							transistor3	=	1;
							if (dp3==1)
							{h=0;}
							break;//
			case 1:	transistor4	=	1;
							if (dp4==1)
							{h=0;}
							break;//
			case 0:	transistor5	=	1;
							if (dp5==1)
								{h=0;}
							if (sign==1)
								{g=0;}

							break;//
		}											//
	counter++;
	if (counter == 6)
		{counter =0x0;}
}
//============================================//
void HelloWorld(void)
{
	dp1=0,dp2=0,dp3=0,dp4=0,dp5=0;
	displayRAM[0]=' ';
	displayRAM[1]='H';
	displayRAM[2]='E';
	displayRAM[3]='L';
	displayRAM[4]='L';
	displayRAM[5]='O';
	sign=0;
}
