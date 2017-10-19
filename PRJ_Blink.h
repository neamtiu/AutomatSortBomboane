/*
 * PRJ_Blink.h
 *
 * Created: 19.10.2017 15:00:31
 *  Author: Dani
 */ 


#ifndef PRJ_BLINK_H_
#define PRJ_BLINK_H_

#include<avr/io.h>

#define RED_led 5//pin 13 (PB5)
#define BLUE_led 4//pin 11 (PB4)
#define GREEN_led 3//pin 12 (PB3)

void PRJ_Blink(int PB_pinNumber);

#endif /* PRJ_BLINK_H_ */