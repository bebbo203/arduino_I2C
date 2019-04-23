#include "clock.h"
#include <avr/io.h>


#define PIN_MASK (1 << 5)
volatile char CLOCK_LEVEL = 0;

/*GIULIA*/

/*inizializzo clock tipo CTC(quindi setto i valori di TCCR giusti) con frequenza 16000 sulla porta 12 */
void clock_start(void)
{
    TCCR1A = (1<<COM1C0);
	TCCR1B = (1<<WGM12)|(1<<CS12)|(1<<CS10);
	
	const uint8_t mask=(1<<6);
	DDRB |= mask;

	OCR1A = 500;
}

/*inizializzo la clock a zero settando la frequenza a zero (da provare)*/

void clock_zero(void)
{
	TCCR1A = (1<<COM1C0);
	TCCR1B = (1<<WGM12)|(1<<CS12)|(1<<CS10);
	
	const uint8_t mask=(1<<6);
	DDRB |= mask;

	OCR1A = 65535;
}

/*GIULIA*/

/*ROBERTO*/

//PIN 11

//f = f_clk / (prescaler * N * (1 + OCR1A))
void clock_pwm(void)
{
    TCCR1A = (1<<COM1A0) | (1<<WGM10) | (1<<WGM11);
	TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS12) | (1<<CS10);

	DDRB |= PIN_MASK;
	
	OCR1A = 50;
	
}

void clock_pwm_zero(void)
{
    TCCR1A = 0;
    TCCR1B = 0;

    DDRB |= PIN_MASK;
    PORTB &= ~PIN_MASK;
}


//Interrupt 
volatile char pos = 1;
ISR(PCINT0_vect)
{
	/*Occhio che non sappiamo per colpa di quale pin
	  è stato invocato l'interrupt. Per questo abbiamo
	  bisogno, quando ne aggiungeremo altri sempre sulla
	  porta PCIE0, di analizzare la PINx relativa al set di
	  pin su quella porta*/


	//Qui si può chiamare un puntatore a funzione.
	//La funzione deve essere molto snella!
	
	CLOCK_LEVEL = (PINB & PIN_MASK) != 0;
	
	if(pos == 0)
	{
		PORTB &= (0 << 7);
		pos = 1;
	}
	else
	{
		PORTB |= (1 << 7); 
		pos = 0;
	}
}

//Inizializza l'interrupt sul pin della clock per monitornarne il livello
void clock_monitor()
{
	
	cli();

	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT5);

	
	sei();
}




/*ROBERTO*/
