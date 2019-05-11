#include <libs/i2c.h>
#include <avr_common/uart.h>


int main(void)
{
	printf_init();

	master_init();

	master_send(0xAA, 0xFF);

}


