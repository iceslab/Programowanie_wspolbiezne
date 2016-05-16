#ifndef _PRODEUCER_CONSUMER_H_ 
#define _PRODEUCER_CONSUMER_H_ 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <mqueue.h>
#include <semaphore.h>


#define QUEUE_NAME_NO_SLASH "queue"
#define QUEUE_NAME "/"QUEUE_NAME_NO_SLASH 

#define BSIZE 3
#define LSIZE 128

typedef struct
{
	int head;
	int tail;
	int count;
	sem_t mutex;
	sem_t empty;
	sem_t full;
	char buffer[BSIZE][LSIZE];
} buffer_t;


#endif