#ifndef clock
#define clock

#include <avr_common/uart.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void clock_start(void);
void clock_zero(void);
void clock_pwm(void);
void clock_pwm_zero(void);
void clock_monitor(void);

#endif
