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

//Sincronizza e pulisce la seriale da residui master-side
void master_sync(char addr, int n)
{
	Queue dummy_queue;
	Queue* d_q = &dummy_queue;

	init_queue(d_q);
	
	for(; n>0; n--)
		enqueue(d_q, 0x00);

    while(d_q->size > 0)
	{
		printf(".");
		master_send(addr, d_q, 1);
	}
	printf("\nSINCRONIZZATO\n");
}

//Sincronizza e pulisce la seriale da residui slave-side
void slave_sync(int n)
{
	Queue dummy_queue, *d_q;
	d_q = &dummy_queue;
	init_queue(d_q);

	for(;n>0;n--)
	{
		printf(".");
		slave_receive(d_q);
	}
	printf("\nSINCRONIZZATO\n");
}

//Invia allo slave addr la coda queue di lenght q->size
void master_send(char addr, Queue* queue, int length){
	
	signal_start();
	while(clock_level() == 1);
	
	write_byte(addr);
	write_bit(W);
	
	//Lo slave non può inviare un NACK
	//qualsiasi cosa differente da un ACK blocca la comunicazione
	int i = 0;
	while(i<length)
	{ 
		while(clock_level() == 1);
		if(read_bit() == ACK)
		{
			write_byte(dequeue(queue));
			i++;
		}
		else
			break;
		
	}
	while(clock_level() == 1);//devo aspettare a mandare lo stop
	//altrimenti lo slave non fa in tempo a leggere


    signal_stop();
}

//Richiedi allo slave addr un messaggio di quantity byte
//da salvare in queue
void master_request(Queue* queue, char addr, int quantity){
	
	signal_start();
	while(clock_level() == 1);

	write_byte(addr);
	write_bit(R);
	while(clock_level() == 1);
	read_bit();
	for(int i=0; i<quantity; i++){
		
		char b = read_byte();
		enqueue(queue,b);
		if(i+1 != quantity){
			write_bit(ACK);
			while(clock_level() == 1);
		}
	}

	write_bit(NACK);
	while(clock_level() == 1); //se non aspetto che la clock torni a 0
							   //lo slave non fa in tempo a leggere il
							   //NACK (non esce dal while(read_bit() == ACK)
	signal_stop();
}

//Invia al master un messaggio salvato in queue di size byte
void slave_send(Queue* queue, int size){
	
	while(!is_start_fired());
	while(clock_level() == 1);
	char addr = read_byte();
	if(addr == SLAVE_ADDR){
		
		if(read_bit() == R){
			write_bit(ACK);
			char ret = dequeue(queue);
			write_byte(ret);
			while(clock_level() == 1);
			/* i<size -> i controlli sulla size non vengono fatti perchè
			 * la request del master mi specifica quanti byte vuole,
			 * il suo NACK arriverà necessariamente.
			 * E' contemplato il caso in cui lo slave cerca di mandare
			 * pacchetti da più byte di quanti richiesti, ma non il caso
			 * in cui ne ha di meno. */
			while(read_bit() == ACK){
				char ret = dequeue(queue);
				write_byte(ret);
				while(clock_level() == 1);
			}
		}
	}
}

//Ricevi dal master un messaggio da salvare in queue
void slave_receive(Queue* queue){
	
	while(!is_start_fired());
	while(clock_level() == 1);
	
	char addr = read_byte();
	printf("%2X\n", addr);
	
	if(addr == SLAVE_ADDR){
		
		if(read_bit() == W){
			while(!is_stop_fired()){
				write_bit(ACK);

				while(clock_level() == 1);
				enqueue(queue, read_byte());
			}
		}
	}
}

//Settare su cutecom il terminatore a LF
//Utility di lettura stringhe da seriale
void read_string(Queue* queue)
{
	char c;
	while((c = usart_getchar()) != 0xA) //terminatore a capo
		enqueue(queue, c);

	//Stringa C: terminatore 0x00
	enqueue(queue, 0x0A);
}

/* usart_putchar() non serve perchè usiamo la printf */

