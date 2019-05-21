#include "write.h"
#include "clock.h"
#include "misc_utils.h"


//PIN SDA: 13 PB7

void write_high()
{
	DDRB |= SDA_MASK;
	PORTB |= SDA_MASK;
}

void write_low()
{
	DDRB |= SDA_MASK;
	PORTB &= ~SDA_MASK;
}

void write_bit(char c){
	DDRB |= 0x80;
	while(clock_level() == 1);
	SDA_CHANGE_LEVEL(get_char_bit(c, 0));
	while(clock_level() == 0);
}

//Le due while (in busy waiting) servono per tenere il segnale stabile durante
//il tick della clock
//CAMBIO SU FRONTE DI DISCESA, QUINDI CLOCK = LOW
void write_byte(char c)
{
	DDRB |= 0x80;
	for(int i=7; i>=0; i--)
	{
		while(clock_level() == 1);
		SDA_CHANGE_LEVEL(get_char_bit(c, i));
		while(clock_level() == 0);
	}
}
