#include <libs/clock.h>
#include <libs/misc_utils.h>
#include <libs/write.h>
#include <libs/queue.h>
#include <util/delay.h>


int main(void)
{	
	clock_start();
	clock_monitor();
	DDRB |= 0x80;
	PORTB &= ~0x80;

	_delay_ms(1000);
	write_byte(0xAA);

	PORTB &= ~0x80;

	while(1)
	{
		;
	}
}

