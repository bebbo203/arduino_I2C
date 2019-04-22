#ifndef queue_h
#define queue_h


char* queue_start;
char* queue_end;


char* init_queue(void);
void enqueue(char* queue, char message);
char dequeue(char* queue);
char peek(char* queue);

#endif
