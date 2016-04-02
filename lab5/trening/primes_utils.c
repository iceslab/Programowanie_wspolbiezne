#include "primes_utils.h"

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
 
void calculate(int begin, int end, int process_number, int* fd)
{
	int primes_number = primes(begin, end);
	printf(
		"Numer procesu: %d, liczby pierwsze: %d\n", 
		process_number, 
		primes_number);
	struct results res = {begin, end, primes_number};
	
	write(fd[WRITE_PIPE], &res, sizeof(res));
}