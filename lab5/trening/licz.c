#include "common.h"
#include "primes_utils.h"

#define INVALID_FD -1

int main(int argc, char** argv)
{
	if(argc == 4)
	{
		int begin, end, process_number;
		char* fifoname = argv[3];

		sscanf(argv[1], "%d", &begin);
		sscanf(argv[2], "%d", &end);
		sscanf(argv[3], "%d", &process_number);

		int fifo = open(FIFO_NAME, O_RDWR);
		
		// Jeśli otwarto plik
		if(fifo != INVALID_FD)
		{
			int primes_number = primes(begin, end);
			printf(
				"Numer procesu: %d, liczby pierwsze: %d\n", 
				process_number, 
				primes_number);
			struct results res = {begin, end, primes_number};
			//fprintf(fifo, "%d %d\n", process_number, primes_number);
			
			int written = write(fifo, &res, sizeof(res));
			close(fifo);
		}
		else
		{
			perror("Nie udało się otworzyć pipe\n");
		}
	} 

	return 0;
}