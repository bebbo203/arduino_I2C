#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../avr_common/uart.h" // this includes the printf and initializes it

#define PIN_MASK 0x80


int in = 0;


ISR(PCINT0_vect)
{
	if(in) in = 0;
	else in = 1;

	printf("%d\n", in);
}



int main(void)
{
	printf_init();
	DDRB &= ~PIN_MASK;
	PORTB |= PIN_MASK;
	PCICR |= (1 << PCIE0);
	PCMSK0 |= PIN_MASK;
	sei();

	while(1)
	{
		//printf("%d\n", PCMSK0);
	}

}
