#include "i2c.h"

char SLAVE_ADDR = -1;

//Porta il master in situazione di inizio.
//SDA HIGH SCL HIGH
void master_init(){
	clock_monitor();
	signal_register_interrupt();

	write_high();
	clock_high();   
}

//Porta lo slave in situazione di inizio.
void slave_init(char addr){
	clock_monitor();
	signal_register_interrupt();
	
	SLAVE_ADDR = addr;
}


void master_send(char addr, Queue* queue, int length){
	signal_start();
	while(clock_level() == 1);
	write_byte(addr);
	write_bit(W);
	while(clock_level() == 1);
	//Che controllo bisogna fare sull'ACK?
	if(read_bit() == ACK){
		
		for(int i=0; i<length; i++){
			
			write_byte(dequeue(queue));
			//Non mi aspetto nessun NACK
			while(clock_level() == 1);
			char ack = read_bit();
			printf("ACK%d: %2x\n", i, ack);
			if(ack == NACK) break;
		}
	}
	
    signal_stop();

}


//quantity è il numero di byte che il master
//richiede allo slave di indirizzo addr
void master_request(Queue* queue, char addr, int quantity){
	
	signal_start();
	while(clock_level() == 1);

	write_byte(addr);
	write_bit(R);
	while(clock_level() == 1);
	read_bit();
	for(int i=0; i<quantity; i++){
		
		char b = read_byte();
		printf("---->%2X\n", b);
		enqueue(queue,b);
		if(i+1 != quantity){
			write_bit(ACK);
			while(clock_level() == 1);
		}
	}
	printf("FINE\n");
	write_bit(NACK);
	signal_stop();
}


void slave_send(Queue* queue, int size){
	
	while(!is_start_fired());
	while(clock_level() == 1);
	char addr = read_byte();
	if(addr == SLAVE_ADDR){
		
		if(read_bit() == R){
			write_bit(ACK);
			do{
				char ret = dequeue(queue);
				printf("%2X\n", ret);
				write_byte(ret);
				//printf("primo->%2X\n", queue->buffer[queue->first]); 
				while(clock_level() == 1);
			}while(read_bit() != NACK && (--size)>0);
			printf("esco\n");
		}
	}
	
}

void slave_receive(Queue* queue){
	
	while(!is_start_fired());
	while(clock_level() == 1);
	
	char addr = read_byte();
	printf("%2X\n", addr);
	
	if(addr == SLAVE_ADDR){
		
		if(read_bit() == W){
			
			printf("ho letto W\n");
			int i = 0;
			write_bit(ACK);
			while(i<3){
				while(clock_level() == 1);
				char mex = read_byte();
				printf("---->%X\n", mex);
				enqueue(queue, mex);
				if(i==2) write_bit(NACK);
				else write_bit(ACK);
				i++;
			}
		}
	}
}
