#include <libs/i2c.h>
#include <avr_common/uart.h>
#include <util/delay.h>


int main(void)
{

	printf_init();
	master_init();

/*	printf("START\n");
	
	Queue Q, *queue;
	queue = &Q;
	init_queue(queue);

	int i;
	for(i=0; i<21; i++){ //anche qui mando un pacchetto in più (vedi sotto)
						 //NB IL MASTER VA SEMPRE RIPULITO!
		master_request(queue, 0x33, 3);
		//printf(">>>%d\n", i);
	}
	//printf("Size: %d\n", queue->size);
	dequeue(queue);
	dequeue(queue);
	dequeue(queue);
	for(i=0;i<60;i++)
		printf("%X\n", dequeue(queue));

	

	printf("END\n");
	
	while(1);
*/

//MASTER_SEND NO SERIALE
/*
	printf_init();
	master_init();

	Queue Q, *queue;
	queue = &Q;

	int i;
	for(i=0; i<11; i++){ //mando sempre un pacchetto in più che mi garantisce la pulizia della seriale
						 //lo slave comunque riceve tutto quello che deve (ossia condizione-1)
						 //in questo modo non ho bisogno di ricompilare tutto ogni volta che ricomincia 
						 //la comunicazione, mi basta fare open/close su cutecom
		init_queue(queue);
		enqueue(queue, 0xAA);
		enqueue(queue, 0xBB);
		enqueue(queue, 0xCC);
		master_send(0x33, queue, 3);
	}
	while(1);
*/
	
//MASTER_SEND SERIALE
	//while(1)
	//{
		//printf("sono nel while\n");
		Queue queue;
		Queue* q = &queue;
		init_queue(q);
		enqueue(q, 0x00);
		master_send(0x33, q, 1);
		printf("parla: \n");
		
		cli();
		read_string(q);
		sei();
		
		printf("ho letto\n");

		master_send(0x33, q, q->size);
		
		printf("Ho inviato\n");

		/*la coda mi si svuota nella master_send
		while(q->size > 0)
			printf("%c", dequeue(q));
		*/	

		printf("\n");
	//}
	
	


}


