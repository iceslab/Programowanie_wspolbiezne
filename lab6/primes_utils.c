#include "primes_utils.h"

int is_prime(int n)
{
	if( n == 1)
		return 0;

	for(int i = 2; i < n; ++i)
	{
		if(n % i == 0)
			return 0;
	}

	return 1;
}

int primes(int begin, int end)
{
	int ret = 0;
	for(; begin < end; ++begin)
	{
		if(is_prime(begin) == 1)
		{
			// printf("%d\n", begin);
			++ret;
		}
	}
	return ret;
}
 
void calculate(int begin, 
			   int end, 
			   int process_number, 
			   int fd[2])
{
	int primes_number = primes(begin, end);
	printf(
		"Numer procesu: %d, liczby pierwsze: %d\n", 
		process_number, 
		primes_number);
	struct results res = {begin, end, primes_number};
	
	write(fd[WRITE_PIPE], &res, sizeof(res));
}

void getSubprocessName(char** subprocessName, 
					   char* argv_0, 
					   char* subprocessDefine)
{
	char* lastSlash = strrchr(argv_0, (int)'/');
	if(NULL != lastSlash)
	{
		int basePathLength = lastSlash - argv_0 + 1;
		int subprocessNameLength = basePathLength + strlen(subprocessDefine) + 1;
		*subprocessName = (char*)malloc(subprocessNameLength * sizeof(char));
		memset(*subprocessName, 0, subprocessNameLength);
		strncpy(*subprocessName, argv_0, basePathLength);
		strcat(*subprocessName, subprocessDefine);
	}
}

void releaseSubprocessName(char** subprocessName)
{
	if(NULL != *subprocessName)
	{
		free(*subprocessName);
		*subprocessName = NULL;	
	}
}

int makeQueues(mqd_t* queue_in, mqd_t* queue_out, int oflag)
{
	struct mq_attr attr;
	attr.mq_msgsize = sizeof(msg_t);
	attr.mq_maxmsg = 8;
	attr.mq_flags = 0;

	*queue_in = mq_open(MQ_IN_NAME, 
					    oflag, 
					    0660, 
					    &attr);
	if(0 > *queue_in)
	{
		perror("Nie udało się utworzyć kolejki in");
		printf("Errno %d, %d\n", errno, *queue_in);
		return 0;
	}

	*queue_out = mq_open(MQ_OUT_NAME, 
						 oflag, 
						 0660, 
						 &attr);
	if(0 > *queue_out)
	{
		mq_close(*queue_in);
		perror("Nie udało się utworzyć kolejki out");
		printf("Errno %d, %d\n", errno, *queue_out);
		return 0;
	}

	return 1;
}

void releaseQueues(mqd_t* queue_in, mqd_t* queue_out)
{
	mq_close(*queue_in);
	mq_close(*queue_out);
}

void unlinkQueues()
{
	if(0 > mq_unlink(MQ_IN_NAME))
		perror("Nie można odłączyć kolejki in");
	if(0 > mq_unlink(MQ_OUT_NAME))
		perror("Nie można odłączyć kolejki out");
}