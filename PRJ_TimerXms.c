/*
 * PRJ_TimerXms.c
 *
 * Created: 18.10.2017 22:31:43
 * Author : Dani
 */ 

#include "PRJ_TimerXms.h"
    
void PRJ_TimerXms(uint16_t value_ms)
{
	uint16_t OCRvalue;
	//Use CTC on OCR1A (working mode4) for Timer1(16 bit)
	TCCR1B |= (1 << WGM12);
	
	//Period = 0,064ms (for 16Mhz clock and 1024 prescaler value) 
	//=> 15625d(3D09h) impulses for 1 second	   
	OCRvalue = value_ms / 0.064;
	OCR1A = OCRvalue;
	
	//Set the prescaler at 1024 + start the timer(starts when prescaler is active)
	TCCR1B |= (1<<CS12) | (1<<CS10);
	
	while(!TIFR1)
	{
		//waits for overflow (passed 1 second)
	}
	
	//stop the timer
	TCCR1B &= 0b11111000;	
}

