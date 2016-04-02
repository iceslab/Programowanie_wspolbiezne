#include "primes_utils.h"

int main(int argc, char** argv)
{
	// printf("%s\n", argv[0]);
	if(argc == 4) 
	{
		int begin = atoi(argv[1]);
		int end = atoi(argv[2]);
		int processes = atoi(argv[3]);
		time_t start_time = time(NULL);
		int fd[2] = {0};
	
		// Jeśli utworzono pipe
		if(PIPE_ERROR != pipe(fd))
		{
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

				if(fork() == 0)
				{
					calculate(proc_begin, proc_end, i, fd);
					exit(0);
				}
			}
		}
		else
		{
			perror("Nie udało się utworzyć pipe");
			exit(0);
		}

		struct results res;
		int proc_number = 0, proc_primes = 0, primes = 0;
		
		for(int i = 0; i < processes; ++i)
		{
			read(fd[READ_PIPE], &res, sizeof(res));
			primes += res.count;
		}

		// Czekanie na procesy
		int status, pid;
		for(int i = 0; i < processes; ++i)
		{
			pid = wait(&status);
			printf("Proces %d zakończony\n", pid);
		}
		start_time = time(NULL) - start_time;
		printf("Liczb pierwszych: %d, czas trwania: %ld s\n", 
			   primes, 
			   start_time);
	}	
	else
	{
		printf("Usage: pierwsze [begin] [end] [processes]\n");
	}

	return 0;
}