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

void start_signal()
{
	//Sono a inizio trasmissione, mi aspetto
	//SDA e SCL HIGH
	write_low();
    //Probabilmente qui serve una pausa
	//Forse può non servire siccome la clock parte HIGH
	//e il primo tick funge da pausa.
	clock_start();
}

void stop_signal()
{
	//Sono a fine trasmissione, mi aspetto
	//SDA e SCL LOW
	clock_high();
    write_high();
}




//Le due while (in busy waiting) servono per tenere il segnale stabile durante
//il tick della clock
void write_byte(char c)
{
	for(int i=0; i<8; i++)
	{
		while(clock_level() == 1);
		SDA_CHANGE_LEVEL(get_char_bit(c, i));
		while(clock_level() == 0);
	}
}
