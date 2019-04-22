#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../avr_common/uart.h" // this includes the printf and initializes it

#define PIN_MASK 0x80


int att = 0, prec=0;;


ISR(PCINT0_vect)
{
	att=TCNT1;
	printf("%d\n", att-prec);
	prec=att;
}



int main(void)
{
	printf_init();
	TCCR1A=0;
	TCNT1=0;
	TCCR1B=(1<<CS10) | (1<<CS12);
	DDRB &= ~PIN_MASK;
	PORTB |= PIN_MASK;
	PCICR |= (1 << PCIE0);
	PCMSK0 |= PIN_MASK;
	sei();

	while(1){
		//printf("%d\n", PCMSK0);
	}

}
