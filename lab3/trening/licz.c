#include <stdio.h>

int is_prime(int n)
{
	for(int i = 2; i < n; ++i)
	{
		if(n % i == 0)
			return 0;
	}

	return 1;
}

int primes(int begin, int end)
{
	int ret = 0;
	for(; begin < end; ++begin)
	{
		if(is_prime(begin) == 1)
		{
			// printf("%d\n", begin);
			++ret;
		}
	}
	return ret;
}

int main(int argc, char** argv)
{
	if(argc == 5)
	{
		int begin, end, process_number;
		char* filename = argv[3];

		sscanf(argv[1], "%d", &begin);
		sscanf(argv[2], "%d", &end);
		sscanf(argv[4], "%d", &process_number);

		FILE* file = fopen(filename, "a");
		
		// Jeśli otwarto plik
		if(file != NULL)
		{
			// char* str = (char*)malloc(sizeof(int) * 8 * 2 + 1 + 1);
			// char* tmp = (char*)malloc(sizeof(int) * 8 + 1);

			// memcpy(str, argv[4], (strlen(argv[4]) + 1) * sizeof(char));
			// strcat(str, " ");
			// strcat(str, itoa(primes(begin, end), tmp, 10));
			int primes_number = primes(begin, end);
			printf(
				"Numer procesu: %d, liczby pierwsze: %d\n", 
				process_number, 
				primes_number);
			fprintf(file, "%d %d\n", process_number, primes_number);
			// fwrite(str, sizeof(char), strlen(str), file);

			fclose(file);
			
		}
		else
			perror("Nie udało się otworzyć pliku\n");
	} 

	return 0;
}