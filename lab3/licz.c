#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int is_prime(int n)
{
	if(n < 2)
		return 0;

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
			// printf("Pid: %d, prime: %d\n", getpid(), begin);
			++ret;
		}
	}
	return ret;
}

int main(int argc, char** argv)
{
	if(argc == 4)
	{
		int begin, end, process_number;

		sscanf(argv[1], "%d", &begin);
		sscanf(argv[2], "%d", &end);
		sscanf(argv[3], "%d", &process_number);

		int primes_number = primes(begin, end);
		printf(
			"Numer procesu: %d, liczby pierwsze: %d\n", 
			process_number, 
			primes_number);
		exit(primes_number);
	} 

	return 0;
}