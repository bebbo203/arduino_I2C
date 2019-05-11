#ifndef signals
#define signals

#include "clock.h"
#include "write.h"
#include "read.h"
#include "misc_utils.h"


extern volatile char REG_PREC;

void signal_start(void);
void signal_stop(void);
void signal_register_interrupt(void);
char is_start_fired(void);
char is_stop_fired(void);


#endif
