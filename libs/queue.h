#ifndef queue_h
#define queue_h

typedef struct Queue Queue;

struct Queue{
	unsigned char buffer[250];
	unsigned char first;
	unsigned char last;
	unsigned char size;
};

void init_queue(Queue* q);
void enqueue(Queue* q, char c);
char dequeue(Queue* q);




#endif
