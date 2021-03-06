#include <libs/i2c.h>
#include <avr_common/uart.h>
#include <util/delay.h>


int main(void)
{

	printf_init();
	master_init();


	
	Queue queue;
	Queue* q = &queue;

	printf("Attesa sincronizzazione");
	master_sync(0x33, 50);

	char length;
	while(1)
	{
		init_queue(q);
	
		printf("\nInserisci un messaggio: \n");
		
		cli();
		read_string(q);
		sei();

		length = q->size;
	   
		printf("Invio del messaggio in corso...\n");
		master_send(0x33, q, length);

		init_queue(q);
		printf("Richiesta dati in corso...\n");
		master_request(q, 0x33, length);

		printf("Messaggio ricevuto:\n>");
		while(q->size > 0)
			printf("%c", dequeue(q));
   
	}

}


