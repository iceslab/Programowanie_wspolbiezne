#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

#define MS_TO_NS(x) x*1000000

int main(void) 
{
	struct timespec t = {0, MS_TO_NS(50)};
	int i,j;
	puts("Witamy w Lab PRW");
	system("hostname");
		for(i=0;i<10;i++) 
		{
			j=i+10;
			printf("Krok %d\n",i);
			nanosleep(&t, NULL);
		}
	printf("Koniec\n");
	return EXIT_SUCCESS;
}
