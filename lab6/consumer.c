#include "producer_consumer.h"

int main(int argc, char** argv)
{
	if(argc == 2)
	{
		struct mq_attr attr;
		attr.mq_msgsize = sizeof(msg_t);
		attr.mq_maxmsg = 3;
		attr.mq_flags = 0;

		mqd_t queue = mq_open(QUEUE_NAME, 
						   	  O_RDWR | O_CREAT, 
						   	  0660, 
						   	  &attr);
		if(queue < 0)
		{
			perror("Nie udało się utworzyć kolejki");
			return 0;
		}

		int steps = atoi(argv[1]);
		int i = 0;
		for(; i < steps; ++i)
		{
			msg_t order;
			unsigned priority = 0;
			mq_receive(queue, (char*)&order, sizeof(msg_t), &priority);
			printf("Konsument %d: %d, %d, %s\n", 
					getpid(), 
					order.type,
					order.nr, 
					order.buf);
			sleep(1);
		}

		mq_close(queue);
	}
	printf("Konsument %d: Koniec\n", 
			getpid());
	return 0;
}
 
