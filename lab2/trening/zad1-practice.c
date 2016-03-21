#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#define MS_TO_NS(x) x*1000000

void function_in_child()
{
	struct timespec t = {0, MS_TO_NS(50)};
	int i;
	for(i = 0; i <= 10; ++i)
	{
		printf("%d/10\n", i);
		nanosleep(&t, NULL);
	}
}

int main(int argc, char** argv)
{
	int pid, status;
	if((pid = fork()) == 0)
	{
		function_in_child();
		exit(0);
	}
	else
	{
		printf("Macierzysty czeka na %d...\n", pid);
		pid = wait(&status);
		printf("Macierzysty doczekał się na %d, status: %d\n", pid, status);	
	}
	
	return 0;
}