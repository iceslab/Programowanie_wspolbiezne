#include "producer_consumer.h"

int main(int argc, char** argv)
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
	}
	getchar();
	mq_close(queue);
	mq_unlink(QUEUE_NAME);

	return 0;
}
