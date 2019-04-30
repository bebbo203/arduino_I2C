#include "write.h"
#include "clock.h"
#include "misc_utils.h"


//PIN SDA: 13 pb7



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


//Le due while (in busy waiting) servono per tenere il segnale stabile durante
//il tick della clock
//CAMBIO SU FRONTE DI DISCESA, QUINDI CLOCK = LOW
void write_byte(char c)
{
	for(int i=0; i<8; i++)
	{
		while(clock_level() == 1);
		SDA_CHANGE_LEVEL(get_char_bit(c, i));
		while(clock_level() == 0);
	}
}