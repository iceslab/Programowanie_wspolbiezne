#ifndef _PRODEUCER_CONSUMER_H_ 
#define _PRODEUCER_CONSUMER_H_ 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <mqueue.h>

#define QUEUE_NAME_NO_SLASH "queue"
#define QUEUE_NAME "/"QUEUE_NAME_NO_SLASH 

typedef struct msg
{
	int type;
	int nr;
	char buf[256];
} msg_t;


#endif