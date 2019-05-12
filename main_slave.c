#include <stdio.h>
#include <libs/clock.h>
#include <libs/read.h>
#include <libs/misc_utils.h>
#include <libs/signals.h>
#include <avr_common/uart.h>


int main(void)
{
    printf_init();
    printf("bebbo fa schifo \n");
    clock_monitor();
    signal_register_interrupt();

	while(1)
	{
		while(!is_start_fired());
		while(clock_level() == 1);

		printf("----------------------------------->START\n");

		printf("%X\n", read_byte());
		printf("%X\n", read_bit());
		write_bit(0);
		for(int i =0;i<3;i++)
		{
				printf("%X\n", read_byte());
				write_bit(0);
		}
		
		//while(!is_stop_fired());



	}

}
