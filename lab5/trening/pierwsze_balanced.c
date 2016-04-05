#include "primes_utils.h"

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
			printf("lastSlash == \"%c\"\n", *lastSlash);
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

		printf("Otwieranie pipe'ów\n");
		fifo_in = open(FIFO_IN_NAME, O_RDWR);
		printf("Ukończono otwieranie pipe'ów\n");

		// Jeśli otwarto pipe'y
		if(fifo_in > 0)
		{
			int proc_begin, proc_end = begin;

			// Rezerwacja pamięci na string
			char str[INT_STR_LENGTH];
			char str_i[INT_STR_LENGTH];
			
			// Tworzenie procesów
			printf("Tworzenie procesów\n");
			for(int i = 1; i <= processes; ++i)
			{
				sprintf(str_i, "%d", i);
				if(fork() == 0)
				{
					// Podmienianie obrazu w pamięci
					execl(subprocessName, 
						  subprocessName, 
						  str_i,
						  NULL);
					perror("Nie udało się utworzyć procesu");
				}
			}
			printf("Ukończono tworzenie procesów\n");

			fifo_out = open(FIFO_OUT_NAME, O_RDONLY | O_NONBLOCK);

			// Zapełnianie kolejki
			printf("Zapełnianie kolejki\n");
			for(int i = 0; i < partitionLength; ++i)
			{
				proc_begin = proc_end;
				proc_end = ((i / (float)partitionLength) * (end - begin)) + begin;

				struct results order = {proc_begin, proc_end, i};
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
			// printf("Otwieranie pipe'ów\n");
			
			// printf("Ukończono otwieranie pipe'ów\n");
			
			struct results res;
			int proc_number = 0, proc_primes = 0, primes = 0;
			
			for(int i = 0; i < processes; ++i)
			{
				printf("Rozpoczęcie czytania\n");
				read(fifo_out, &res, sizeof(res));
				printf("Koniec czytania\n");
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

		if(NULL != subprocessName)
		{
			free(subprocessName);
			subprocessName = NULL;	
		}
	}	
	else
	{
		printf("Usage: pierwsze [begin] [end] [processes] [partition length]\n");
	}

	return 0;
}