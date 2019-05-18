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
	//printf("PRE_START PINB: %2X\n", PINB);
	signal_start();
	while(clock_level() == 1);
	
	write_byte(addr);
	write_bit(W);
	while(clock_level() == 1);
	//Non è contemplato che lo slave mi mandi un NACK,
	//non può decidere di interrompere la conversazione
	int i = 0;
	while(i<length){ 
		
		if(read_bit() == ACK){
	
			write_byte(dequeue(queue));
			//Non mi aspetto nessun NACK
			while(clock_level() == 1);
			//printf("ACK%d: %2x\n", i, ack);
			
			i++;
		}
		else{
			i == length;
			while(clock_level() == 1);
			printf("sblock\n");
			break;
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
		//printf("---->%2X\n", b);
		enqueue(queue,b);
		if(i+1 != quantity){
			write_bit(ACK);
			while(clock_level() == 1);
		}
	}

	write_bit(NACK);
	//printf("FINE\n");
	while(clock_level() == 1); //se non aspetto che la clock torni a 0
							   //lo slave non fa in tempo a leggere il
							   //NACK (non esce dal while(read_bit() == ACK)
	signal_stop();
}


void slave_send(Queue* queue, int size){
	
	//int i = 1;
	while(!is_start_fired());
	while(clock_level() == 1);
	char addr = read_byte();
	if(addr == SLAVE_ADDR){
		
		if(read_bit() == R){
			write_bit(ACK);
			char ret = dequeue(queue);
			//printf("%2X\n", ret);
			write_byte(ret);
			//printf("primo->%2X\n", queue->buffer[queue->first]); 
			while(clock_level() == 1);
			//i++;
			/* i<size -> i controlli sulla size non vengono fatti perchè
			 * la request del master mi specifica quanti byte vuole,
			 * il suo NACK arriverà necessariamente.
			 * E' contemplato il caso in cui lo slave cerca di mandare
			 * pacchetti da più byte di quanti richiesti, ma non il caso
			 * in cui ne ha di meno. */
			while(read_bit() == ACK){
				char ret = dequeue(queue);
				//printf("%2X\n", ret);
				write_byte(ret);
				//printf("primo->%2X\n", queue->buffer[queue->first]); 
				while(clock_level() == 1);
				//i++;
			}
			//printf("esco\n");
		}
	}
	return;	
}


void slave_receive(Queue* queue){
	
	while(!is_start_fired());
	while(clock_level() == 1);
	
	char addr = read_byte();
	printf("%2X\n", addr);
	
	if(addr == SLAVE_ADDR){
		
		if(read_bit() == W){
			
			//da sistemare con caso generico 
			int i = 0;
			while(i<3){
				write_bit(ACK);
				while(clock_level() == 1);
				enqueue(queue, read_byte());
				i++;
			}
		}
	}
}

//Settare su cutecom il terminatore a LF 
void read_string(Queue* queue)
{
	char c;

	while((c = usart_getchar()) != 0xA)
		enqueue(queue, c);
}

