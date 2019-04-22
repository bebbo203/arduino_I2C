#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../avr_common/uart.h" // this includes the printf and initializes it
#include <../libs/queue.h>
#include <../libs/misc_utils.h>

//In questo programma si attiva un interrupt al cambio
//di stato del
//PIN 12.

#define PIN_MASK (1 << 6) 

volatile int CLOCK_LEVEL = 0;


ISR(PCINT0_vect)
{
	CLOCK_LEVEL = (PINB & PIN_MASK) != 0;
	//printf("%d\n",CLOCK_LEVEL);
}

void init_clock(void)
{
	cli();
	
	DDRB &= ~PIN_MASK;
	PORTB |= PIN_MASK;

	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT6);

	sei();
}

//Write on pin 13
void init_write(void)
{
	DDRB |= (1 << 7);
	PORTB &= 011111111;

}



void write(void)
{
	char i=8;
	char n=0;
	char send = 0xAA;
	while(n<i)
	{
		while(CLOCK_LEVEL == 1);
		if(get_char_bit(send, n))
		{
			printf("WRITING 1\n");
			PORTB |= (1<<7);
		}
		else
			printf("WRITING 0\n");
		while(CLOCK_LEVEL == 0);
		PORTB &= 011111111;
		n++;
	}
}



int main(void)
{
	printf_init();
	init_clock();
	init_write();

    write();

}

