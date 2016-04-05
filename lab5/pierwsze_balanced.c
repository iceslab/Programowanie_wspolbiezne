#include "primes_utils.h"
#include <math.h>

int main(int argc, char** argv)
{
	// printf("%s\n", argv[0]);
	if(argc == 5) 
	{
		int begin = atoi(argv[1]);
		int end = atoi(argv[2]);
		int processes = atoi(argv[3]);
		int partitionLength = atoi(argv[4]);
		time_t start_time = time(NULL);
		int fifo_in = 0;
		int fifo_out = 0;
		int initResult = INITIALIZE_SUCCESS;

		char* subprocessName = NULL;
		char* lastSlash = strrchr(argv[0], (int)'/');
		if(NULL != lastSlash)
		{
			int basePathLength = lastSlash - argv[0] + 1;
			int subprocessNameLength = basePathLength + strlen(SUBPROCESS_BALANCED_NAME) + 1;
			subprocessName = (char*)malloc(subprocessNameLength * sizeof(char));
			memset(subprocessName, 0, subprocessNameLength);
			strncpy(subprocessName, argv[0], basePathLength);
			strcat(subprocessName, SUBPROCESS_BALANCED_NAME);
		}

		if(MKFIFO_SUCCESS != mkfifo(FIFO_IN_NAME, PERMISSIONS))
		{
			perror("mkfifo_in");
		}

		if(MKFIFO_SUCCESS != mkfifo(FIFO_OUT_NAME, PERMISSIONS))
		{
			perror("mkfifo_out");
		}

		// Rezerwacja pamięci na string
		char str_i[INT_STR_LENGTH];

		// Tworzenie procesów
		printf("Tworzenie procesów\n");
		for(int i = 1; i <= processes; ++i)
		{
			sprintf(str_i, "%d", i);
			int fork_res = fork();
			if(fork_res == 0)
			{
				// Podmienianie obrazu w pamięci
				execl(subprocessName, 
					  subprocessName, 
					  str_i,
					  NULL);
				perror("Nie udało się utworzyć procesu");
			}
			printf("Utworzono proces %d (%d)\n", i, fork_res);
		}
		printf("Ukończono tworzenie procesów\n");


		printf("Otwieranie pipe IN\n");
		fifo_in = open(FIFO_IN_NAME, O_RDWR);
		printf("Ukończono otwieranie pipe IN\n");		
		// printf("Otwieranie pipe OUT\n");
		// fifo_out = open(FIFO_OUT_NAME, O_RDONLY);
		// printf("Ukończono otwieranie pipe OUT\n");

		// Jeśli otwarto pipe'y
		if(fifo_in > 0)
		{
			int proc_begin, proc_end = begin;
			int parts = (int)ceil((float)(end - begin) / (float)partitionLength);

			// Zapełnianie kolejki
			printf("Zapełnianie kolejki\n");
			for(int i = 0; i < parts; ++i)
			{
				proc_begin = proc_end;
				proc_end = ((i / (float)parts) * (end - begin)) + begin;

				struct results order = {proc_begin, proc_end, i};
				write(fifo_in, &order, sizeof(order));
			}

			for(int i = 0; i < processes; ++i)
			{
				struct results order = {-1, -1, -1};
				write(fifo_in, &order, sizeof(order));
			}
			printf("Ukończono zapełnianie kolejki\n");
		}
		else
		{
			perror("Nie udało się utworzyć pipe");
			initResult = INITIALIZE_FAIL;
		}

		// Jeśli udało się utworzyć pipe i procesy potomne
		if(INITIALIZE_SUCCESS == initResult)
		{
			// printf("Otwieranie pipe OUT\n");
			fifo_out = open(FIFO_OUT_NAME, O_RDONLY);
			// printf("Ukończono otwieranie pipe OUT\n");

			struct results res;
			int proc_number = 0, proc_primes = 0, primes = 0;
			int bytes_read = 0;
			do
			{
				// printf("Rozpoczęcie czytania\n");
				bytes_read = read(fifo_out, &res, sizeof(res));
				// printf("Koniec czytania\n");
				primes += res.count;
			}while(bytes_read > 0);

			printf("Rozpoczęcie czekania na procesy\n");
			// Czekanie na procesy
			int status, pid;
			for(int i = 0; i < processes; ++i)
			{
				pid = wait(&status);
				printf("Proces %d zakończony\n", pid);
			}
			printf("Koniec czekania na procesy\n");

			start_time = time(NULL) - start_time;
			printf("Liczb pierwszych: %d, czas trwania: %ld s\n", 
				   primes, 
				   start_time);
		}

		if(NULL != subprocessName)
		{
			free(subprocessName);
			subprocessName = NULL;	
		}

		close(fifo_in);
		fifo_in = INVALID_FD;
	}	
	else
	{
		printf("Usage: pierwsze [begin] [end] [processes] [partition length]\n");
	}

	return 0;
}