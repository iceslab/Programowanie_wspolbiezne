#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#define SIZE 80 
#define SECTOR_SIZE 512
#define INVALID_FD -1

int main(int argc, char** argv) 
{ 
    if(argc == 3)
    {
        // Bufor wielkości sektora dysku
        char buf[SECTOR_SIZE] = {0};
        // Deskryptory plikow
        int file1 = INVALID_FD, file2 = INVALID_FD; 

        // Otwarcie pliku 1 w odpowiednim trybie
        file1 = open(argv[1], O_RDONLY); 

        // Jeśli plik 1 jest otwarty
        if(file1 != INVALID_FD) 
        {
            // Otwarcie pliku 3 w odpowiednim trybie
            file2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU); 
            
            // Jeśli plik 2 jest otwarty
            if(file2 != INVALID_FD)
            {
                // Ilość przeczytanych bajtów
                int bytes_read = 0;

                // Pętla kopiująca plik
                do
                {
                    bytes_read = read(file1, buf, SECTOR_SIZE);
                    write(file2, buf, bytes_read);
                } while(bytes_read == SECTOR_SIZE);
            }
            else
            {
                perror("Nie udało się otworzyć pliku nr 1");
            }
        }
        else
        {
            perror("Nie udało się otworzyć pliku nr 2");
        }
        
        // Zamknij pliki jeśli otwarte
        if(file1 != INVALID_FD)
            close(file1);  
        if(file2 != INVALID_FD)
            close(file2);  
    }
    else
    {
        printf("Nieprawidłowa ilość argumentów (%d): podaj dwa argumenty\n"
               "copy [src] [dst]\n", 
               argc - 1);
    }
    
    return 0; 
}
