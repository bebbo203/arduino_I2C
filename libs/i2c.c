#include "i2c.h"

char SLAVE_ADDR = -1;

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
	SLAVE_ADDR = addr;
}


void master_send(char addr, char* queue, int length)
{
	signal_start();
	while(!is_start_fired());
	write_byte(addr);
	write_bit(W);
	//Che controllo bisogna fare sull'ACK?
	if(read_bit() == ACK)
	{
		for(int i=0; i<length; i++)
		{
			write_byte(dequeue(queue));
			//Non mi aspetto nessun NACK
			read_bit();
		}
	}

	signal_stop();
	}


//quantity è il numero di byte che il master
//richiede allo slave di indirizzo addr
char* master_request(char addr, int quantity)
{
	signal_start();
	while(!is_start_fired());
	char* queue = init_queue();
	write_byte(addr);
	write_bit(R);
	//Si suppone che si riceva sempre l'ack
	//siccome l'indirizzo immesso è sempre
	//presente.
	read_bit();
	for(int i=0; i<quantity; i++)
	{
		enqueue(queue,read_byte());
		write_bit(ACK);
	}

	write_bit(NACK);
	return queue;
}


void slave_send(char* queue, int size)
{
	while(!is_start_fired());
	char addr = read_byte();
	if(addr == SLAVE_ADDR)
	{
		if(read_bit() == R)
		{
			write_bit(ACK);
			do
			{
				write_byte(dequeue(queue));
			}while(read_bit() != NACK);
		}
	}
	
}