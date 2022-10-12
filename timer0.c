#include	<reg51.h>
#include	<definition.h>
#include <display.h>
#include <serial.h>
#define T0HHH 0xFF
#define T0LLL 0x76
#define T0H 0xFC
#define T0L 0X65 //for 1m sec delay @ 11.592MHz

/*====================================
use formula
x = delay * freq/12

eg 0.003 * 16000000/12 = 2765 = 0x0FA0 =>0xFFFF - 0x0FA0	=0xF05F
eg 0.003 * 16000000/12 = 13333 =0x3415 =>0xFFFF - 0x3415	=0xCBEA
====================================*/
//bit clock30ms=0, clock3ms=0;
void InitTimer0 (void)
{
	TH0 = T0H;
	TL0 = T0L;
 	TMOD = TMOD | 0X01;// timer-0 mode-1 16 BIT
	IE = IE | 0X82;//enable global-0x80 & T0-0x02 interrupts
	TR0=1;
}

void timer0 (void) interrupt 1
{	
	static bit echodelay=0;
	turnoff();
	errorcount++;
	if (errorcount==0xFF)
			{HelloWorld();}
	if (echodelay==0)
		{
			TH0 = T0HHH;//caclulated in initialize timer0
			TL0 = T0LLL;//caclulated in initialize timer0			
			echodelay=1;
		}
	else
		{
			internaldisplay();
			TH0 = T0H;//caclulated in initialize timer0
			TL0 = T0L;//caclulated in initialize timer0			
			echodelay=0;
		}
}