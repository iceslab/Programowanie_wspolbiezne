#include "primes_utils.h"

int main(int argc, char** argv)
{
	if(argc == 4) 
	{
		int begin = atoi(argv[1]);
		int end = atoi(argv[2]);
		int processes = atoi(argv[3]);
		time_t start_time = time(NULL);
		int fifo = 0;

		char* subprocessName = NULL;
		char* lastSlash = strrchr(argv[0], (int)'/');
		if(NULL != lastSlash)
		{
			int basePathLength = lastSlash - argv[0] + 1;
			int subprocessNameLength = basePathLength + strlen(SUBPROCESS_NAME) + 1;
			subprocessName = (char*)malloc(subprocessNameLength * sizeof(char));
			memset(subprocessName, 0, subprocessNameLength);
			strncpy(subprocessName, argv[0], basePathLength);
			strcat(subprocessName, SUBPROCESS_NAME);
		}

		if(MKFIFO_SUCCESS != mkfifo(FIFO_OUT_NAME, PERMISSIONS))
		{
			perror("mkfifo");
		}

		fifo = open(FIFO_OUT_NAME, O_RDWR);
		// Jeśli otwarto pipe
		if(fifo <= 0)
		{
			perror("Nie udało się utworzyć pipe");
			exit(0);
		}
		else
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

				sprintf(str_beg, "%d", proc_begin);
				sprintf(str_end, "%d", proc_end);
				sprintf(str_i, "%d", i);

				if(fork() == 0)
				{
					// Podmienianie obrazu w pamięci
					execl(subprocessName, 
						  subprocessName, 
						  str_beg, 
						  str_end,
						  str_i,
						  NULL);
					perror("Nie udało się utworzyć procesu");
					exit(0);
				}
			}

			if(NULL != subprocessName)
			{
				free(subprocessName);
				subprocessName = NULL;	
			}
		}

		struct results res;
		int proc_number = 0, proc_primes = 0, primes = 0;
		
		for(int i = 0; i < processes; ++i)
		{
			read(fifo, &res, sizeof(res));
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