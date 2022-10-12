#include <reg51.h>
#include <definition.h>
#include <combined.h>
#include <display.h>
#define BAUDNUM9600 -12 // @11.0592MHz and PCON.7=1
#define BufferLength 0x10
bit flag = 0, stable=0,foundCR=0;
unsigned char uartbuffer[BufferLength];
unsigned char errorcount=0;

void init_serial(void)
{
	TMOD = TMOD | 0x20;
	PCON = PCON & 0X7F;	//normal speed	
	SCON = 0X50;				//serial mode-2, REN=1
	TH1=BAUDNUM9600;	
	IE = IE | 0x90;	//enable global-ox80 serial 0x10		
	TR1 = 1;
}
	
void uart (void)	interrupt 4
{
	static unsigned char counter;
	unsigned char receivedbyte;
	RI = 0;
	receivedbyte = 0x7F & SBUF;
	
	if (flag == 1)
			{
				uartbuffer[counter]=receivedbyte; 
				counter++;
				//end of buffer 
				if (receivedbyte==CR)
					{flag = 0; counter=0; foundCR=1;}				
				if (counter == BufferLength)
					{flag = 0;counter=0;}
				//CR found before end of buffer
			}
		else
			{
				if (receivedbyte == CR)
					{counter = 0;foundCR=1;}
				else
					{
						if ((foundCR == 1) && (receivedbyte == LF))
								{
									counter = 0;
									flag = 1;
									foundCR=0;
									errorcount=0;
									ClearDisplay();
									NT_10byte();
								}
						else
							{	flag = 0;	foundCR=0;}
					}
			}
}
