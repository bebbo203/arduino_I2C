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
    //printf("bebbo fa schifo \n");
    slave_init(0x33);
	
	//PROVA SLAVE_RECEIVE
	printf(" START\n");
	Queue Q, *queue;
	queue = &Q;
	init_queue(queue);
	
	int i;
	while(queue->size<10) {
		slave_receive(queue);
		printf("size: %d\n", queue->size);
	}
	while(queue->size>0) dequeue(queue);
	printf("prontoooo\n");
	
	while(1){
		//printf("prima\n");
		slave_receive(queue);
		//printf("sec\n");
		
		//printf("--->FINITO REC-> dim : %d\n", queue->size)
		while(queue->size>0){
			printf("%c", dequeue(queue));
		}
		printf(" FINE\n");
	}
	
	
	//PROVA SLAVE_SEND
	/*
	struct Queue Q, *queue;
	queue = &Q;
	
	int i;
	printf("inizio\n");
	for(i=0; i<20;i++){
		init_queue(queue);
		enqueue(queue, 0xAA);
		enqueue(queue, 0xAB);
		enqueue(queue, 0xAC);
		
		slave_send(queue, 3); 
		//printf("e: %d\n", i);
	}
	
	printf("fine\n");*/
	//while(1);
	



}
