#ifndef COMMON_H
#define COMMON_H

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
#include <errno.h>
#include <sys/mman.h>

#define INT_STR_LENGTH sizeof(int)*8+1
#define INVALID_FD -1
#define PIPE_ERROR -1
#define SLEEP_ERROR -1
#define USLEEP_ERROR -1
#define PIPE_COUNT 3
#define READ_PIPE 0
#define WRITE_PIPE 1
#define ITERATIONS 10
#define SLEEP_SEC 1U
#define SLEEP_USEC 100U*1000U
#define MAX_BUFFER_LENGTH 512
#define SMALL_BUFFER_LENGTH 64
#define MAX_PROCESSES 300
#define MQ_ERROR (mqd_t)-1

#endif