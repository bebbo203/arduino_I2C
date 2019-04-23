#ifndef clock
#define clock

#include <avr_common/uart.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void clock_start(void);
void clock_zero(void);

#endif
