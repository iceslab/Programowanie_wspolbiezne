#include "common.h"

int main(int argc, char* argv[])
{
	int fd[2] = {0};

	if(pipe(fd) == PIPE_ERROR)
	{
		perror("Nie udało się utowrzyć łącza");
	}
	else
	{
		if(fork() == 0)
		{
			
			int number = 0, i = 1;
			for(; i <= ITERATIONS; ++i)
			{
				read(fd[READ_PIPE], &number, sizeof(int));
				printf("Potomny: odczytano liczbę %d\n", number);
			}
			exit(0);
		}

		int i = 1;
		for(; i <= ITERATIONS; ++i)
		{
			write(fd[WRITE_PIPE], &i, sizeof(int));
			printf("Macierzysty: zapisano liczbę %d\n", i);
			if(usleep(SLEEP_USEC) == USLEEP_ERROR)
				perror("Nie można uśpić");
		}

		int status = 0;
		int pid = wait(&status);
		printf("Proces %d zakończył się z kodem: %d\n", pid, WEXITSTATUS(status));
	}

	return 0;
} 
