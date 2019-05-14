#include "clock.h"
#include <avr/io.h>

//PIN 11 (PIN_MASK)

//frequenza settata con OCR a 50
//f = f_clk / (prescaler * N * (1 + OCR1A))

volatile char CLOCK_LEVEL = 0;

//TCCR sono settate per avere la PWM
void clock_start(void)
{
    TCCR1A = (1<<COM1A0) | (1<<WGM10) | (1<<WGM11);
	TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS12) | (1<<CS10);

	DDRB |= SCL_MASK;
	
	OCR1A = 1000;
	
}

//porto la clock a zero azzerando i TCCR (sto sempre sil pin 11)
void clock_zero(void)
{
    TCCR1A = 0;
    TCCR1B = 0;

    DDRB |= SCL_MASK;
    PORTB &= ~SCL_MASK;
}

//porto la clock ad un livello alto
void clock_high(void)
{
	//con questi non funziona
    TCCR1A = 0;
	TCCR1B &= ~(1 << CS12) & ~(1<<CS10);
	DDRB |= SCL_MASK;
	PORTB |= SCL_MASK;
}




//Inizializza l'interrupt sul pin della clock per monitornarne il livello
void clock_monitor()
{
	
	cli();

	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT5);
	
	sei();
}

char clock_level()
{
	return CLOCK_LEVEL;
}
