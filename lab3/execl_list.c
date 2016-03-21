#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#define MS_TO_NS(x) x*1000000

int main(int argc, char** argv)
{
	int pid, child, parent;
	parent = getpid();
	char* str = (char*)malloc(sizeof(int)*8+1);
	printf("Rozpoczęcie procesu macierzystego, pid %d\n", getpid());
	for(child = 2; child < argc; ++child)
	{
		// Jeśli dziecko
		if((pid = fork()) == 0)
		{
			sprintf(str, "%d", child - 1);
			printf("./sub_exec sub_exec %s %s\n", argv[child], str);
			execl("./sub_exec", "sub_exec", argv[child], str, NULL);
			perror("execl");
		}
	}

	free(str);
	
	// Jeśli rodzic
	if(getpid() == parent)
	{
		printf("Rozpoczęcie pętli procesu macierzystego, pid %d\n", getpid());
		struct timespec t = {0, MS_TO_NS(50)};
		int i;
		int steps = atoi(argv[1]);
		for(i = 0; i <= steps; ++i)
		{
			printf("Macierzysty, krok %d/%d\n", i, steps);
			nanosleep(&t, NULL);
		}
		printf("Zakończenie pętli procesu macierzystego, pid %d\n", getpid());
	}

	int i, status;
	for(i = 0; i < argc - 2; ++i)
	{
		pid = wait(&status);
		printf("Proces %d, zakończony: kod %d\n", pid, WEXITSTATUS(status));
	}
	printf("Zakończenie procesu macierzystego, pid %d\n", getpid());
	return 0;
}