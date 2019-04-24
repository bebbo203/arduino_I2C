#ifndef write
#define write

#include "clock.h"

#define SDA_MASK 0x80
#define SDA_CHANGE_LEVEL(c) if(c==1) { PORTB |= SDA_MASK;} else { PORTB &= ~SDA_MASK;}

void write_high(void);
void write_low(void);
void start_signal(void);
void stop_signal(void);
void write_byte(char c);



#endif
