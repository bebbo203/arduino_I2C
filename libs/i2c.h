#ifndef i2c
#define i2c

#include "clock.h"
#include "write.h"
#include "read.h"
#include "signals.h"
#include "misc_utils.h"
#include "queue.h"
#include "util/delay.h"

#define W 0
#define R 1
#define ACK 0
#define NACK 1


void master_init(void);
void slave_init(char addr);
void master_send(char addr, char* queue, int length);
char* master_request(char addr, int quantity);



#endif
