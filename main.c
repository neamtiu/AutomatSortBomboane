/*
 * Test.c
 *
 * Created: 19.10.2017 17:04:54
 * Author : Dani
 */ 
#define F_CPU 16000000UL
#define RED_led 5//pin 13 (PB5)
#define BLUE_led 4//pin 11 (PB4)
#define GREEN_led 3//pin 12 (PB3)
#define Middle 3000	//pulses
#define Right 2000 //pulses
#define Left 4000 //pulses


#include <avr/io.h>
#include <util/delay.h>

void PRJ_TimerXms(uint16_t value_ms)
{
	uint16_t OCRvalue;
	
	//reset timer control registers
	TCCR1A = 0;
	TCCR1B = 0;
	ICR1 = 0;
	//reset the timer
	TCNT1 = 0;
	//Use CTC on OCR1A (working mode4) for Timer1(16 bit)
	TCCR1B |= (1 << WGM12);
	
	//Period = 0,064ms (for 16Mhz clock and 1024 prescaler value)
	//=> 15625d(3D09h) impulses for 1 second
	OCRvalue = value_ms / 0.064;
	OCR1A = OCRvalue;
	
	//Set the prescaler at 1024 + start the timer(starts when prescaler is active)
	TCCR1B |= (1<<CS12) | (1<<CS10);
	
	while(TCNT1 != OCR1A)
	{
		//waits for overflow (passed 1 second)
	}
	TIFR1 &= ~(1 << TOV1);
	
	//stop the timer
	TCCR1B &= 0b11111000;
}

void PRJ_BlinkLed(uint8_t PB_pinSelect)
{
	DDRB |= (1<<PB_pinSelect);//put the specified pin in output mode
	PORTB |= (1<<PB_pinSelect);//set the specified pin

	PRJ_TimerXms(1000);//wait 1s
	
	PORTB &= ~(1<<PB_pinSelect);//unset the specified pin
}

void PRJ_Servo(uint16_t position)
{
	//reset timer control registers
	TCCR1A = 0;
	TCCR1B = 0;
	ICR1 = 0;
	//reset the timer
	TCNT1 = 0;
	//set port b pin 1 as pwm output
	DDRB |= (1<<PORTB1);
	//use timer1 in fast pwm mode using ICR1 as TOP
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	//use pwm in non-inverted mode
	TCCR1A |= (1 << COM1A1);
	//set top value 39999d (20ms)
	ICR1 = 39999;
	//set OCR1A in order to go to the specified position
	OCR1A = position;	
	//set prescaler at 8 and start the timer
	TCCR1B|=  (1<<CS11);
}

int main(void)
{
	    while (1) 
    {
	    PRJ_Servo(Middle);
	    //_delay_ms(1000);
		PRJ_TimerXms(1000);
	    PRJ_Servo(Right);
	    //_delay_ms(1000);
		PRJ_TimerXms(1000);
	    PRJ_Servo(Left);
	    // _delay_ms(1000);
		PRJ_TimerXms(1000);
		/*
		OCR1A = 3000;
		_delay_ms(1000);
		OCR1A = 4000;
		_delay_ms(1000);
		OCR1A = 2000;
		_delay_ms(1000);
		*/

    }
}

