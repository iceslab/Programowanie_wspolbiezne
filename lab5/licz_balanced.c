#include "common.h"
#include "primes_utils.h"

#define INVALID_FD -1

int main(int argc, char** argv)
{
	if(argc == 2)
	{
		int begin, end, process_number;
		struct results res = {0};
		sscanf(argv[1], "%d", &process_number);

		//printf("Proces %d: Otwieranie pipe IN\n", process_number);
		int fifo_in = open(FIFO_IN_NAME, O_RDONLY);
		//printf("Proces %d: Ukończono otwieranie pipe IN\n", process_number);

		//printf("Proces %d: Otwieranie pipe OUT\n", process_number);
		int fifo_out = open(FIFO_OUT_NAME, O_WRONLY);
		//printf("Proces %d: Ukończono otwieranie pipe OUT\n", process_number);
		
		// Jeśli otwarto pipe'y
		if(fifo_in > 0 && fifo_out > 0)
		{
			// printf("Proces %d: Rozpoczęcie czytania\n", process_number);
			while(read(fifo_in, &res, sizeof(res)) > 0)
			{
				begin = res.begin;
				end = res.end;

				if(res.begin == -1)
					break;

				int primes_number = primes(begin, end);
				// printf("Numer procesu: %d, liczby pierwsze: %d\n", 
				// 	   process_number, 
				// 	   primes_number);

				res.begin = begin;
				res.end = end;
				res.count = primes_number;
				// printf("Proces %d: Rozpoczęcie pisania\n", process_number);
				int written = write(fifo_out, &res, sizeof(res));
				// printf("Proces %d: Koniec pisania\n", process_number);
			}
			// printf("Proces %d: Koniec czytania\n", process_number);
			close(fifo_in);
			close(fifo_out);
		}
		else
		{
			perror("Nie udało się otworzyć pipe\n");
		}
		printf("Proces %d: Koniec działania\n", process_number);
	} 

	return 0;
}