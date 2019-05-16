#include <libs/i2c.h>
#include <avr_common/uart.h>
#include <util/delay.h>


int main(void)
{

	/*printf_init();
	master_init();

	printf("START\n");
	
	Queue Q, *queue;
	queue = &Q;
	init_queue(queue);

	master_request(queue, 0x33, 3);

	for(int i=0;i<3;i++)
		printf("%X\n", dequeue(queue));

	

	printf("END\n");
	
	while(1);*/

	printf_init();
	master_init();

	Queue Q, *queue;
	queue = &Q;
	init_queue(queue);

	enqueue(queue, 0xAA);
	enqueue(queue, 0xBB);
	enqueue(queue, 0xCC);

	master_send(0x33, queue, 3);
	
}


