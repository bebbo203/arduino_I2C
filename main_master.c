#include <libs/clock.h>
#include <libs/misc_utils.h>
#include <libs/write.h>
#include <libs/queue.h>
#include <util/delay.h>
#include <libs/signals.h>
#include <avr_common/uart.h>

int main(void)
{
	printf_init();
	//clock_start();
	clock_high();
	clock_monitor();
	signal_register_interrupt();
	DDRB |= 0x80;
	PORTB |= 0x80;

	signal_start();
	_delay_ms(100);

	write_byte(0xBE);
	write_byte(0xBB);
	write_byte(0x00);
	
	PORTB &= ~0x80;

	while(1)
	{
		;
	}
}

