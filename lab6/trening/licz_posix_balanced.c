#include "common.h"
#include "primes_utils.h"

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		mqd_t queue_in, queue_out;

		makeQueues(&queue_in, &queue_out);

		if(MQ_ERROR == queue_in || MQ_ERROR == queue_out)
		{
			perror("Nie udało się utworzyć kolejki");
			exit(0);
		}
		else
		{
			msg_t order;
			unsigned priority = 0;
			while(1)
			{
				printf("Potomny %d: Odbieranie\n", 
					   getpid());
				mq_receive(queue_in, 
						   (char*)&order, 
						   sizeof(msg_t), 
						   &priority);
				printf("Potomny %d: Odebrano\n", 
					   getpid());
				if(order.number < 0)
				{
					printf("Potomny %d: Koniec\n", getpid());
					break;
				}
					

				order.count = primes(order.begin, order.end);
				printf("Numer procesu: %d, liczby pierwsze: %d\n", 
					   getpid(), 
					   order.count);
				
				mq_send(queue_out, (char*)&order, sizeof(msg_t), 10);
			}

			//releaseQueues(&queue_in, &queue_out);
		}
	} 
	return 0;
}