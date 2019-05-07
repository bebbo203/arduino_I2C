#include <stdio.h>
#include <libs/clock.h>
#include <libs/read.h>
#include <avr_common/uart.h>


int main(void){
	printf_init();
	printf("bebbo fa schifo \n");
	clock_monitor();
	signal_register_interrupt();

	while(!is_start_fired());
	
	printf("%2x\n", read_byte());
		
	
}
