#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "primes_utils.h"

#define INT_STR_LENGTH sizeof(int)*8+1
#define INVALID_FD -1

int main(int argc, char** argv)
{
	// printf("%s\n", argv[0]);
	if(argc == 4) 
	{
		int begin = atoi(argv[1]);
		int end = atoi(argv[2]);
		int processes = atoi(argv[3]);
		char* filename = "wynik.txt";
		time_t start_time = time(NULL);

		// Utwórz puty plik z wynikami
		int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	
		// Jeśli otwarto plik
		if(file != INVALID_FD)
		{
			close(file);
			int proc_begin, proc_end = begin;

			// Rezerwacja pamięci na string
			char str[INT_STR_LENGTH];
			char str_beg[INT_STR_LENGTH];
			char str_end[INT_STR_LENGTH];
			char str_i[INT_STR_LENGTH];
			// Tworzenie procesów
			for(int i = 1; i <= processes; ++i)
			{
				proc_begin = proc_end;
				proc_end = ((i / (float)processes) * (end - begin)) + begin;

				sprintf(str_beg, "%d", proc_begin);
				sprintf(str_end, "%d", proc_end);
				sprintf(str_i, "%d", i);
				if(fork() == 0)
				{
					// Podmienianie obrazu w pamięci
					execl("./licz", 
						  "licz", 
						  str_beg, 
						  str_end,
						  filename, 
						  str_i,
						  NULL);
					perror("Nie udało się utworzyć procesu");
				}
			}
		}
		else
		{
			perror("Nie udało się otworzyć pliku");
			exit(0);
		}

		// Czekanie na procesy
		int status, pid;
		for(int i = 0; i < processes; ++i)
		{
			pid = wait(&status);
			printf("Proces %d zakończony\n", pid);
		}
		
		
		file = open(filename, O_RDWR);

		if(file != INVALID_FD)
		{
			struct results res;
			int proc_number = 0, proc_primes = 0, primes = 0;
			
			for(int i = 0; i < processes; ++i)
			{
				read(file, &res, sizeof(res));
				//fscanf(file, "%d %d\n", &proc_number, &proc_primes);
				primes += res.count;
			}

			start_time = time(NULL) - start_time;
			printf("Liczb pierwszych: %d, czas trwania: %ld s\n", 
				   primes, 
				   start_time);
			dprintf(file, 
				    "Liczb pierwszych: %d, czas trwania: %ld s\n", 
				    primes, 
				    start_time);
			// write(file, buf, strlen(buf));
		}
	}	
	else
	{
		printf("Usage: pierwsze [begin] [end] [processes]\n");
	}

	return 0;
}