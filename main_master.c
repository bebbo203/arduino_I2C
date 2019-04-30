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
	clock_start();
	clock_monitor();
	signal_register_interrupt();
	DDRB |= 0x80;
	PORTB &= ~0x80;

	//_delay_ms(1000);
	write_byte(0x0E);

	PORTB &= ~0x80;

   

	while(1)
	{
		;
	}
}

