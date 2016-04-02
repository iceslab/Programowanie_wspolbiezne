#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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
