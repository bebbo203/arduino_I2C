#include "signals.h"
#include <util/delay.h>

#define INT_MASK 0xA0

volatile char REG_PREC = 0;

char start, stop;

char is_start_fired()
{
	if(start){
		start=0;
		return 1;
	}
	return start;
}

char is_stop_fired(){
	if(stop){
		stop=0;
		return 1;
	}
	return stop;
}

ISR(PCINT0_vect)
{
	/*Occhio che non sappiamo per colpa di quale pin
	  è stato invocato l'interrupt. Per questo abbiamo
	  bisogno, quando ne aggiungeremo altri sempre sulla
	  porta PCIE0, di analizzare la PINx relativa al set di
	  pin su quella porta*/


	//Qui si può chiamare un puntatore a funzione.
	//La funzione deve essere molto snella!

	
	REG_PREC &= INT_MASK;

	

	switch(REG_PREC ^ (PINB & INT_MASK))
	{
	case 0x20:{//clock
		CLOCK_LEVEL = (PINB & SCL_MASK) != 0;
		break;
	}
	case 0x80:{//pin
		if(clock_level() && !get_char_bit(PINB, 7))
			start=1;
		else
		{
			if(clock_level() && get_char_bit(PINB,7))
				stop = 1;
		}
		break;
	}
	}

	REG_PREC = PINB;
	
}

void signal_start()
{
	//Sono a inizio trasmissione, mi aspetto
	//SDA e SCL HIGH
	write_low();
    //Probabilmente qui serve una pausa
	//Forse può non servire siccome la clock parte HIGH
	//e il primo tick funge da pausa.
	clock_start();
	_delay_ms(100);
}

void signal_stop()
{
	//Sono a fine trasmissione, mi aspetto che sono in questa condizione:
	//SDA e SCL LOW
	clock_high();
    write_high();
	_delay_ms(100);
}

void signal_register_interrupt(void)
{
	start=0;
	stop=0;
	PCMSK0 |= (1 << PCINT7);
}


