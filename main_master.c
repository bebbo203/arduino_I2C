#include <libs/i2c.h>
#include <avr_common/uart.h>
#include <util/delay.h>


int main(void)
{
	printf_init();

	master_init();

	char* queue = init_queue();
	enqueue(queue, 0xBE);
	enqueue(queue, 0xBE);
	enqueue(queue, 0x01);
	master_send(0xAA, queue, 3);

	_delay_ms(1000);
	enqueue(queue, 0xB0);
	enqueue(queue, 0xB1);
	enqueue(queue, 0x00);
	master_send(0xAA, queue, 3);
		

	while(1);

}


