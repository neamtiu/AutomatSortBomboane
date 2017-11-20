/*
 * PRJ_Servo.c
 *
 * Created: 31.10.2017 23:29:25
 * Author : Dani
 */ 


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

