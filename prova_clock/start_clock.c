#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "../avr_common/uart.h"	// this includes the printf and initializes it


//WGM setta il tipo di pwm che voglio (fast, phase correct, ctc...)
//COM setta il comportamento di OC:
//          o lo azzera o lo setta nel momento del match (invertita o no)
//CS setta il prescaler

//STIAMO UTILIZZANDO CTC

//https://www.arduinoslovakia.eu/application/timer-calculator

//OCR dice la frequenza


//PIN 12. Quando ci pare possiamo cambiarlo.

#define TCCRA_MASK (1<<COM1B0)
#define TCCRB_MASK (1<<WGM12)|(1<<CS12)|(1<<CS10)
int main(void)
{

	TCCR1A=TCCRA_MASK;
	TCCR1B=TCCRB_MASK;

	const uint8_t mask=(1<<6);
	DDRB |= mask;

	OCR1A = 16000;
	
	while(1);

}
