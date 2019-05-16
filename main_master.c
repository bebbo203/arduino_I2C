#include <libs/i2c.h>
#include <avr_common/uart.h>
#include <util/delay.h>


int main(void)
{
	printf_init();


	master_init();

	printf("START\n");
	
	Queue Q, *queue;
	queue = &Q;

	master_request(queue, 0x33, 3);

	for(int i=0;i<3;i++)
		printf("%2X\n", dequeue(queue));

	

	printf("END\n");
	
	while(1);
	
}


