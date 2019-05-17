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
	printf(" START\n");
	//PROVA SLAVE_RECEIVE
	
	Queue Q, *queue;
	queue = &Q;
	init_queue(queue);
	int k;
	for(k=0; k<20; k++){
		//printf("RECIVE BLOCK: %d\n", k);
		slave_receive(queue);
	}
	int i;
	printf("--->FINITO REC-> dim : %d\n", queue->size);
	for(i=0; i<60; i++){
		printf("%X\n", dequeue(queue));
	}
	printf(" FINE\n");
	
	while(1);
	
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
	
	printf("fine\n");
	while(1);
	
	
	//PROVA PRIMITIVE
	/*
	int i=0;
	while(!is_start_fired());
	while(clock_level() == 1);
	for(i=0; i<10; i++){
				while(clock_level() == 1);
		char ret = read_byte();
		printf("%2X\n", ret);

		write_byte(ret);
	}
	while(1); */
	
	


}
