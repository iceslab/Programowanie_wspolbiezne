#ifndef PRIMES_UTILS_H
#define PRIMES_UTILS_H

#include "common.h"

struct results
{
	int begin;
	int end;
	int count;
};

int is_prime(int n);
int primes(int begin, int end);
void calculate(int begin, int end, int process_number, int* fd);

#endif