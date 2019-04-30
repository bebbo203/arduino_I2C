#include "read.h"
#include "clock.h"
#include "misc_utils.h"


//leggo sul fronte di salita della clock 

char read_bit(){
	char c=0;
	while(clock_level()==0);
	c |= (get_char_bit(PINB, 7));
	return c;
}
