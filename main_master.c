#include <libs/clock.h>
#include <libs/misc_utils.h>
#include <libs/queue.h>
#include <util/delay.h>

int main(void)
{
	

	DDRB |= (1 << 7);
	PORTB &= (0 << 7);

	clock_pwm();
	clock_monitor();

	while(1);
}
