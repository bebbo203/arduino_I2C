#include "queue.h"

char queue[128];

char* init_queue()
{
	queue_start = 0;
	//end punta sempre al primo spazio vuoto
	queue_end = queue;
	return queue_end;
}

void enqueue(char* queue, char message)
{
    if(queue_start == 0)
	{
		queue_start = queue;
		*queue_start = message;
		queue_end = queue_start+1;
	}
	else
		*(queue_end++) = message;
}

char dequeue(char* queue)
{
	char ret;

	if(queue_start == 0 || queue_start == queue_end)
		return -1;
	else
	{
		ret = *queue_start;
		*queue_start = 0;
		queue_start++;
		return ret;
	}
}

char peek(char* queue)
{
	char ret;
	if(queue_start == 0 || queue_start == queue_end)
		return -1;
	else
	{
		ret = *queue_start;
		return ret;
	}
}
