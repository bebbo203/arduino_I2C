#include "read.h"
#include "clock.h"
#include "misc_utils.h"


//Leggo sul fronte di salita della clock 
char read_bit(){
	DDRB &= ~0x80;
	char c=0;
	while(clock_level()==0);
	c |= (get_char_bit(PINB, 7));
	while(clock_level()==1);
	return c != 0;
}

//Faccio ciclo di lettura su 8 bit e ritorno il char 
char read_byte(){
	int n=7;
	char c=0;
	
	while(n>=0){
		if(read_bit())
			c=set_char_bit(c,n);
		n--;
	}
	
	return c;
}
