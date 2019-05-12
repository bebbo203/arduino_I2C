#include <libs/i2c.h>
#include <avr_common/uart.h>


int main(void)
{
	printf_init();

	master_init();

	char* queue = init_queue();
	enqueue(queue, 0xBE);
	enqueue(queue, 0xBB);
	enqueue(queue, 0x00);

	master_send(0xAA, queue, 3);

}


