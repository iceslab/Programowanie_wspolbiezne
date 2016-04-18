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

			mq_receive(queue_in, (char*)&order, sizeof(msg_t), &priority);

			order.count = primes(order.begin, order.end);
			printf("Numer procesu: %d, liczby pierwsze: %d\n", 
				   getpid(), 
				   order.count);
			
			mq_send(queue_out, (char*)&order, sizeof(msg_t), 10);
		}
	} 
	return 0;
}