#ifndef PRIMES_UTILS_H
#define PRIMES_UTILS_H

#define FIFO_IN_NAME "primes_fifo_in"
#define FIFO_OUT_NAME "primes_fifo_out"
#define PERMISSIONS 0666
#define MKFIFO_SUCCESS 0
#define INITIALIZE_FAIL 1
#define INITIALIZE_SUCCESS 0
#define SUBPROCESS_NAME "licz"
#define SUBPROCESS_BALANCED_NAME "licz_balanced"
#define SUBPROCESS_POSIX_NAME "licz_posix"
#define SUBPROCESS_POSIX_BALANCED_NAME "licz_posix_balanced"

#define MQ_IN_NAME "/"MQ_IN_NAME_NO_SLASH
#define MQ_OUT_NAME "/"MQ_OUT_NAME_NO_SLASH

#define MQ_IN_NAME_NO_SLASH "in"
#define MQ_OUT_NAME_NO_SLASH "out"

#include "common.h"

struct results
{
	int begin;
	int end;
	int count;
};

typedef struct primes
{
	int number;
	int begin;
	int end;
	int count;
} msg_t;

typedef struct timespec timespec_t;

int is_prime(int n);
int primes(int begin, int end);
void calculate(int begin, 
			   int end, 
			   int process_number, 
			   int* fd);
void getSubprocessName(char** subprocessName, 
					   char* argv_0, 
					   char* subprocessDefine);
void releaseSubprocessName(char** subprocessName);
int makeQueues(mqd_t* queue_in, mqd_t* queue_out, int oflag);
void releaseQueues(mqd_t* queue_in, mqd_t* queue_out);
void unlinkQueues();
timespec_t diff(timespec_t start, timespec_t end);

#endif