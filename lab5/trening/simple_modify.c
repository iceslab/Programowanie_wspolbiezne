#include "common.h"

int main(int argc, char* argv[])
{
	int fd[PIPE_COUNT][2] = {0};
	int i = 0, result = 0;
	for(; i < PIPE_COUNT; ++i)
	{
		result = pipe(fd[i]);
		if(PIPE_ERROR == result)
			break;
	}

	if(PIPE_ERROR == result)
	{
		perror("Nie udało się utworzyć łącza");
	}
	else
	{
		// Pierwszy i drugi proces dziecko (na schemacie P2, P3)
		for(i = 0; i < 2; ++i)
		{
			if(fork() == 0)
			{
				int number = 0, j = 1;
				for(; j <= ITERATIONS; ++j)
				{
					read(fd[i][READ_PIPE], &number, sizeof(int));
					printf("P%d: odczytano liczbę %d z fd[%d]\n", i + 1, number, i);
					++number;
					write(fd[i + 1][WRITE_PIPE], &number, sizeof(int));
					printf("P%d: zapisano liczbę %d do fd[%d]\n", i + 1, number, i + 1);
				}
				exit(0);
			}
		}

		// Proces macierzysty (na schemacie P1)
		for(i = 1; i <= ITERATIONS; ++i)
		{
			write(fd[0][WRITE_PIPE], &i, sizeof(int));
			printf("Macierzysty: zapisano liczbę %d\n", i);
			if(usleep(SLEEP_USEC) == USLEEP_ERROR)
				perror("Nie można uśpić");
		}

		int number = 0;
		for(i = 1; i <= ITERATIONS; ++i)
		{
			read(fd[2][READ_PIPE], &number, sizeof(int));
			printf("Macierzysty: odczytano liczbę %d\n", number);
		}

		int status = 0, pid = 0;
		for(i = 0; i < 2; ++i)
		{
			pid = wait(&status);
			printf("Proces %d zakończył się z kodem: %d\n", pid, WEXITSTATUS(status));	
		}
	}

	return 0;
} 
