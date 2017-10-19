/*
 * PRJ_Blink.c
 *
 * Created: 19.10.2017 14:59:13
 * Author : Dani
 */ 

#include "PRJ_Blink.h"

void PRJ_Blink(uint8_t PB_pinSelect)
{
	DDRB |= (1<<PB_pinSelect);//put the specified pin in output mode
	PORTB |= (1<<PB_pinSelect);//set the specified pin

	PRJ_TimerXms(1000);//wait 1s
	
	PORTB &= ~(1<<PB_pinSelect);//unset the specified pin
}

