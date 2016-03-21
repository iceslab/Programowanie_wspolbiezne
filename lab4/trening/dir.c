#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#include <dirent.h>

#define SECTOR_SIZE 512
#define TRUE 1
#define FALSE 0
#define INVALID_FD -1
#define SUCCEED 0
#define MIN_RIGHTS_LENGTH 11

int makeRights(struct stat* stats, char* buf, int bufSize);
void printStats(char* filename);

int main(int argc, char** argv) 
{ 
    if(argc <= 2)
    {
        char* dirPath = NULL;

        // Przypisanie nazwy katalogu jeśli podana w argumencie
        if(argc == 2)
        {
            dirPath = argv[2];
        }
        // Jeśli nie podana w argumencie, przypisanie domyślnej
        else
        {
            dirPath = "./";
        }

        // Otwieranie katalogu
        DIR* dirStream = opendir(dirPath);

        if(dirStream == NULL)
        {
            perror("Nie można otworzyć katalogu");
        }
        else
        {
            struct dirent* dirEntry = NULL;
            do
            {
                dirEntry = readdir(dirStream);
                if(dirEntry == NULL)
                {
                    break;
                }
                else
                {
                    printStats((*dirEntry).d_name);
                    printf("\n");    
                }
            } while(TRUE);
        }
    }
    else
    {
        printf("Nieprawidłowa ilość argumentów (%d): podaj jeden argument\n"
               "fstat [file]\n", 
               argc - 1);
    }
    
    return 0; 
}
