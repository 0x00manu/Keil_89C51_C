#include <reg51.h>
#include <definition.h>
#include <timer0.h>
#include <serial.h>
#include <display.h>

void main(void) 
{
	HelloWorld();
	InitTimer0();													//needed for keypad and testkeys
	init_serial();
	while(1);
}