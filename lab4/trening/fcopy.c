#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#define SIZE 80 
#define SECTOR_SIZE 512
#define INVALID_FD NULL

int main(int argc, char** argv) 
{ 
    if(argc == 3)
    {
        // Bufor wielkości sektora dysku
        char buf[SECTOR_SIZE] = {0};
        // Deskryptory plikow
        FILE *file1 = INVALID_FD, *file2 = INVALID_FD; 

        // Otwarcie pliku 1 w trybie read only
        file1 = fopen(argv[1], "r"); 

        // Jeśli plik 1 jest otwarty
        if(file1 != INVALID_FD) 
        {
            // Otwarcie pliku 3 w trybie write, create or truncate
            file2 = fopen(argv[2], "w"); 
            
            // Jeśli plik 2 jest otwarty
            if(file2 != INVALID_FD)
            {
                // Ilość przeczytanych bajtów
                int bytes_read = 0;

                // Pętla kopiująca plik
                do
                {
                    bytes_read = fread(buf, sizeof(char), SECTOR_SIZE, file1);
                    fwrite(buf, sizeof(char), bytes_read, file2);
                } while(!feof(file1));

                printf("Zakończono kopiowanie\n%s  =>  %s\n", 
                       argv[1], 
                       argv[2]);
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
            fclose(file1);  
        if(file2 != INVALID_FD)
            fclose(file2);  
    }
    else
    {
        printf("Nieprawidłowa ilość argumentów (%d): podaj dwa argumenty\n"
               "fcopy [src] [dst]\n", 
               argc - 1);
    }
    
    return 0; 
}
