#include "i2c.h"

char SLAVE_ADD = -1;

//Porta il master in situazione di inizio.
//SDA HIGH SCL HIGH
void master_init()
{
	clock_monitor();
	signal_register_interrupt();
	write_high();
	clock_high();		
}

//Porta lo slave in situazione di inizio.
void slave_init(char addr)
{
	clock_monitor();
	signal_register_interrupt();
	SLAVE_ADD = addr;
}


void master_send(char addr, char msg)
{
	signal_start();
	write_byte(addr);
	write_bit(W);
	//Che controllo bisogna fare sull'ACK?
	read_bit();
	write_byte(msg);
	//Che controllo bisogna fare sull'ACK?
	read_bit();
	signal_stop();
}
