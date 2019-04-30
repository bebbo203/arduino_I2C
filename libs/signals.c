#include "signals.h"

#define INT_MASK 0xA0

volatile char REG_PREC = 0;

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
	case 0x20:{
		CLOCK_LEVEL = (PINB & SCL_MASK) != 0;
		break;
	}
	case 0x80:{
		printf("0x80\n");
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
}

void signal_stop()
{
	//Sono a fine trasmissione, mi aspetto
	//SDA e SCL LOW
	clock_high();
    write_high();
}

void signal_register_interrupt(void)
{
	PCMSK0 |= (1 << PCINT7);
}


