#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "primes_utils.h"

#define INVALID_FD -1

int main(int argc, char** argv)
{
	if(argc == 5)
	{
		int begin, end, process_number;
		char* filename = argv[3];

		sscanf(argv[1], "%d", &begin);
		sscanf(argv[2], "%d", &end);
		sscanf(argv[4], "%d", &process_number);

		int file = open(filename, O_WRONLY | O_APPEND);
		
		// Jeśli otwarto plik
		if(file != INVALID_FD)
		{
			int primes_number = primes(begin, end);
			printf(
				"Numer procesu: %d, liczby pierwsze: %d\n", 
				process_number, 
				primes_number);
			struct results res = {begin, end, primes_number};
			//fprintf(file, "%d %d\n", process_number, primes_number);
			
			lockf(file, F_LOCK, 0);
			write(file, &res, sizeof(res));
			lockf(file, F_ULOCK, 0);
			close(file);
		}
		else
			perror("Nie udało się otworzyć pliku\n");
	} 

	return 0;
}