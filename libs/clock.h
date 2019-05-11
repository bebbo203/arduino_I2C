#ifndef clock
#define clock

#include <avr/io.h>
#include <avr/interrupt.h>

#define SCL_MASK 0x20

extern volatile char CLOCK_LEVEL;

void clock_start(void);
void clock_zero(void);
void clock_high(void);
void clock_pwm(void);
void clock_pwm_zero(void);
void clock_monitor(void);
void clock_wait_low(void);
char clock_level(void);

#endif
