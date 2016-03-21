#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#define MS_TO_NS(x) x*1000000

int main(int argc, char** argv)
{
	int steps, child_num;
	steps = atoi(argv[1]);
	child_num = atoi(argv[2]);
	// sprintf(argv[1], "%d", &steps);
	// sprintf(argv[2], "%d", &child_num);
	printf("Rozpoczęcie procesu potomnego %d, pid %d\n", child_num, getpid());
	struct timespec t = {0, MS_TO_NS(50)};
	int i;
	for(i = 0; i <= steps; ++i)
	{
		printf("Potomny %d, krok %d/%d\n", child_num, i, steps);
		nanosleep(&t, NULL);
	}
	printf("Koniec procesu potomnego %d, pid %d\n", child_num, getpid());
	exit(child_num);
}