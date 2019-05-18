#include <stdio.h>
#include <libs/i2c.h>

int main(void)
{
	printf_init();



	while(1)
	{
		Queue queue;
		Queue* q = &queue;
		init_queue(q);

		read_string(q);

		while(q->size > 0)
			printf("%c", dequeue(q));

		printf("\n");
	}
	



}




