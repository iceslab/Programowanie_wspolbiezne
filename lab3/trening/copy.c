#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#define SIZE 80 
#define SECTOR_SIZE 512

int main(int argc, char** argv) 
{ 
    if(argc == 3)
    {
        // Bufor wielkości sektora dysku
        char buf[SECTOR_SIZE] = {0};
        // Deskryptory plikow
        int file1, file2; 

        // Otwarcie plikow w odpowiednim trybie
        file1 = open(argv[1], O_RDONLY); 
        file2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);

        // Jeśli oba pliki są otwarte
        if(file1 >= 0 && file2 >= 0) 
        { 
            // Ilość przeczytanych bajtów
            int bytes_read = 0;

            // Pętla kopiująca plik
            do
            {
                bytes_read = read(file1, buf, SECTOR_SIZE);
                write(file2, buf, bytes_read);
            }while(bytes_read == SECTOR_SIZE);
        } 
        
        // Zamknij pliki jeśli otwarte
        if(file1 >= 0)
            close(file1);  
        if(file2 >= 0)
            close(file2);  
    }
    else
    {
        printf("Nieprawidłowa ilość argumentów (%d): podaj dwa argumenty\n", argc - 1);
    }
    
    return 0; 
}
