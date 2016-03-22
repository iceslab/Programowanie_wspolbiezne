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
 
