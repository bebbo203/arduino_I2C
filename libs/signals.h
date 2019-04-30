#ifndef signals
#define signals

#include "clock.h"
#include "write.h"
#include "read.h"
#include <avr_common/uart.h>


extern volatile char REG_PREC;

void signal_start(void);
void signal_stop(void);
void signal_register_interrupt(void);


#endif
