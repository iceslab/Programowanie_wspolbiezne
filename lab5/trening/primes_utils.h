#ifndef PRIMES_UTILS_H
#define PRIMES_UTILS_H

#define FIFO_IN_NAME "primes_fifo_in"
#define FIFO_OUT_NAME "primes_fifo_out"
#define PERMISSIONS 0666
#define MKFIFO_SUCCESS 0
#define INITIALIZE_FAIL 1
#define INITIALIZE_SUCCESS 0
#define SUBPROCESS_NAME "licz"
#define SUBPROCESS_BALANCED_NAME "licz_balanced"

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