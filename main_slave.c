#include <stdio.h>
#include <libs/clock.h>
#include <libs/read.h>
#include <libs/misc_utils.h>
#include <libs/signals.h>
#include <avr_common/uart.h>
#include <libs/i2c.h>
#include <util/delay.h>


int main(void)
{
    printf_init();
    slave_init(0x33);
    
	slave_sync(10);
	
	Queue Q, *queue, *q_clone, copia;
	queue = &Q;
	init_queue(queue);
	q_clone = &copia;
	
	while(1){
		slave_receive(queue);
		
		clone(queue, q_clone);
		
		slave_send(queue, queue->size);
		
		printf("Ho ricevuto: ");
		while(q_clone->size>0) printf("%c", dequeue(q_clone));

	}

}
