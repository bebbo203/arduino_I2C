#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void init_queue(Queue* q){
    q->first = 0;
	q->last = 0;
	q->size = 0;
}

void enqueue(Queue* q, char c){
	if(q->size == 0){
		q->buffer[0] = c;
		q->first = 0;
		q->last = 0;
	}
	else{
		q->last++;
		q->buffer[(q->last)] = c;
	}

	q->size++;
	
}

char dequeue(Queue* q){
	char ret;
	
	ret = q->buffer[q->first++];
	if(q->first > q->last){
		q->first = 0;
		q->last = 0;
	}

	q->size--;

    return ret;
}
/*
int main(void){
	Queue Q;
	Queue *q = &Q;
	init_queue(q);

	for(int i=0;i < 50; i++)
	{
		enqueue(q, i);
		enqueue(q, i);
	}

	for(int i=0;i<105; i++)
		printf("%d\n", dequeue(q));
}*/
