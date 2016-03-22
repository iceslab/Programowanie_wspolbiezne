#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#include "fstat_utils.h"

#define SECTOR_SIZE 512
#define TRUE 1
#define FALSE 0
#define INVALID_FD -1
#define SUCCEED 0

int main(int argc, char** argv) 
{ 
    if(argc == 2)
    {
        printStats(argv[1]);
    }
    else
    {
        printf("Nieprawidłowa ilość argumentów (%d): podaj jeden argument\n"
               "fstat [file]\n", 
               argc - 1);
    }
    
    return 0; 
}

