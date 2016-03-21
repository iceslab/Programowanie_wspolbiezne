#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	if(argc == 4) 
	{
		int begin = atoi(argv[1]);
		int end = atoi(argv[2]);
		int processes = atoi(argv[3]);
		time_t start_time = time(NULL);

		
		int proc_begin, proc_end = begin;

		char str[sizeof(int)*8+1];
		char str_beg[sizeof(int)*8+1];
		char str_end[sizeof(int)*8+1];
		char str_i[sizeof(int)*8+1];
		
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
				execl(
					"./licz", 
					"licz", 
					str_beg, 
					str_end, 
					str_i,
					0);
				perror("Nie udało się utworzyć procesu\n");
			}
		}

		// Czekanie na procesy
		int status, pid, primes = 0;
		for(int i = 0; i < processes; ++i)
		{
			pid = wait(&status);
			printf("Proces %d zakończony\n", pid);
			primes += WEXITSTATUS(status);
		}
		
		// int proc_number = 0, proc_primes = 0, primes = 0;
		// for(int i = 0; i < processes; ++i)
		// {
		// 	fscanf(file, "%d %d\n", &proc_number, &proc_primes);
			
		// }

		start_time = time(NULL) - start_time;
		double overall_time = (double)start_time;		
		printf(
			"Liczb pierwszych: %d, czas trwania: %f s\n", 
			primes, 
			overall_time);
		// fprintf(
		// 	file, 
		// 	"Liczb pierwszych: %d, czas trwania: %ld s\n", 
		// 	primes, 
		// 	start_time);
			


	}	

	return 0;
}