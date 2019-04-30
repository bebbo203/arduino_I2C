#include <stdio.h>
#include <libs/clock.h>
#include <libs/read.h>
#include <avr_common/uart.h>

int main(void){
	printf_init();
	printf("bebbo fa schifo \n");
	clock_monitor();
	while(1){
		printf("bit %2x\n", read_bit());
	}
}
