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
#

int makeRights(struct stat* stats, char* buf, int bufSize);

int main(int argc, char** argv) 
{ 
    if(argc == 2)
    {
        // Struktura przechowująca zebrane dane
        struct stat buf;
        // Deskryptor pliku
        int file = INVALID_FD;

        // Otwarcie pliku w trybie read only
        file = open(argv[1], O_RDONLY); 

        // Jeśli plik jest otwarty
        if(file != INVALID_FD) 
        {
            // Jeśli funkcja się powiodła
            if(fstat(file, &buf) == SUCCEED)
            {
                char rightsBuf[MIN_RIGHTS_LENGTH];

                printf("Plik: %s\n", argv[1]);
                printf("wielkość: %ld B => %.1lf KiB\n", 
                       buf.st_size, 
                       buf.st_size / 1024.0);
                printf("wielkość na dysku: %ld B => %.1lf KiB\n", 
                       SECTOR_SIZE * buf.st_blocks,  
                       SECTOR_SIZE * buf.st_blocks/ 1024.0);
                printf("liczba dowiązań twardych: %lu\n", buf.st_nlink);
                
                printf("pozwolenia: ");
                if(makeRights(&buf, rightsBuf, MIN_RIGHTS_LENGTH) == TRUE)
                {
                    printf("%s\n", rightsBuf);
                }
                else
                {
                    printf("nie można odczytać\n");
                }
                
                printf("link symboliczny: %s\n", (S_ISLNK(buf.st_mode) ? "tak" : "nie"));
            }
            else
            {
                perror("Nie udało się uzyskać parametrów pliku");
            }
        }
        else
        {
            perror("Nie udało się otworzyć pliku");
        }
        
        // Zamknij plik jeśli otwarty
        if(file != INVALID_FD)
            close(file);  
    }
    else
    {
        printf("Nieprawidłowa ilość argumentów (%d): podaj jeden argument\n"
               "fstat [file]\n", 
               argc - 1);
    }
    
    return 0; 
}

int makeRights(struct stat* stats, char* buf, int bufSize)
{
    int result = FALSE;

    if(bufSize >= MIN_RIGHTS_LENGTH)
    {
        buf[0] = (S_ISDIR((*stats).st_mode)) ? 'd' : '-';
        buf[0] = (S_ISLNK((*stats).st_mode)) ? 'l' : '-';
        buf[1] = (((*stats).st_mode) & S_IRUSR) ? 'r' : '-';
        buf[2] = (((*stats).st_mode) & S_IWUSR) ? 'w' : '-';
        buf[3] = (((*stats).st_mode) & S_IXUSR) ? 'x' : '-';
        buf[4] = (((*stats).st_mode) & S_IRGRP) ? 'r' : '-';
        buf[5] = (((*stats).st_mode) & S_IWGRP) ? 'w' : '-';
        buf[6] = (((*stats).st_mode) & S_IXGRP) ? 'x' : '-';
        buf[7] = (((*stats).st_mode) & S_IROTH) ? 'r' : '-';
        buf[8] = (((*stats).st_mode) & S_IWOTH) ? 'w' : '-';
        buf[9] = (((*stats).st_mode) & S_IXOTH) ? 'x' : '-';
        buf[10] = '\0';
        result = TRUE;
    }
    else
    {
        result = FALSE;
    }

    return result;
}