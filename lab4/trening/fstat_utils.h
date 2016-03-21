#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 

#define SECTOR_SIZE 512
#define TRUE 1
#define FALSE 0
#define INVALID_FD -1
#define SUCCEED 0
#define MIN_RIGHTS_LENGTH 11

int makeRights(struct stat* stats, char* buf, int bufSize);

void printStats(char* filename);