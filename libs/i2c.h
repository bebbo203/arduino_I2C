#ifndef i2c
#define i2c

#include "clock.h"
#include "write.h"
#include "read.h"
#include "signals.h"
#include "misc_utils.h"
#include "queue.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr_common/uart.h>

#define W 0
#define R 1
#define ACK 0
#define NACK 1


void master_init(void);
void slave_init(char addr);
void master_send(char addr, Queue* queue, int length);
void master_request(Queue* queue, char addr, int quantity);
void slave_receive(Queue* queue);
void slave_send(Queue* queue, int size);
void read_string(Queue* queue);
void master_sync(char addr, int n);
void slave_sync(int n);



#endif
