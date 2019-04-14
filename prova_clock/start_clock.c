#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "./avr_common/uart.h"	// this includes the printf and initializes it


//WGM setta il tipo di pwm che voglio (fast, phase correct, ctc...)
//COM setta il comportamento di OC:
//          o lo azzera o lo setta nel momento del match (invertita o no)
//CS setta il prescaler
#define TCCRA_MASK (1<<COM1C0)
#define TCCRB_MASK (1<<WGM12)|(1<<CS10)|(1<<CS12)
int main(void)
{

	TCCR1A=TCCRA_MASK;
	TCCR1B=TCCRB_MASK;

	//OCR1 è attaccato al pin 13 (quello del LED)
	const uint8_t mask=(1<<7);
	DDRB |= mask;

	OCR1A=0;
	while(1);

}
