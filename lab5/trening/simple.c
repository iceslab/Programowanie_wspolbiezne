#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define PIPE_ERROR -1
#define SLEEP_ERROR -1
#define USLEEP_ERROR -1
#define ITERATIONS 10
#define SLEEP_SEC 1U
#define SLEEP_USEC 100U*1000U

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
				read(fd[0], &number, sizeof(int));
				printf("Potomny: odczytano liczbę %d\n", number);
			}
			exit(0);
		}

		int i = 1;
		for(; i <= ITERATIONS; ++i)
		{
			write(fd[1], &i, sizeof(int));
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
