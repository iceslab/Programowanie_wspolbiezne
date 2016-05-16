#include "primes_utils.h" 

#define REQUIRED_ARGC 4
#define BUF_SIZE 512

typedef struct
{
	int begin;
	int end;
	int sum;
} data_t;

typedef struct
{
	int dimension;
	data_t data[BUF_SIZE];
} buf_t;

void usage(void)
{
	printf("pierwsze_semafory [begin] [end] [processes]\n");
}

int main(int argc, char** argv)
{
	if(REQUIRED_ARGC != argc)
	{
		usage();
		return 1;
	}

	buf_t *buf = NULL;
	buf = (buf_t*) mmap(NULL, 
						sizeof(buf_t), 
						PROT_READ | PROT_WRITE, 
						MAP_SHARED | MAP_ANONYMOUS,
						-1, 
						0);

	if(MAP_FAILED == buf)
	{
		perror("mmap");
		return errno;
	}

	int begin = atoi(argv[1]);
	int end = atoi(argv[2]);
	int processes = atoi(argv[3]);

	int i = 0;
	int proc_begin = 0, proc_end = begin;
	int successfull_processes = processes;

	for(; i < processes; i++)
	{
		proc_begin = proc_end;
		proc_end = (((i + 1) / (float)processes) * (end - begin)) + begin;

		int forkResult = fork();
		
		// Potomny
		if(0 == forkResult)
		{
			buf->data[i].begin = proc_begin;
			buf->data[i].end = proc_end;
			buf->data[i].sum = primes(proc_begin, proc_end);
			exit(0);
		}
		// Macierzysty blad
		else if(0 > forkResult)
		{
			perror("fork");
			--successfull_processes;
		}
	}

	int status = 0, pid = 0;
	// Czekanie na procesy
	for(i = 0; i < successfull_processes; i++)
	{
		pid = wait(&status);
	}

	int sum = 0;
    // Sumowanie wynikow
	for(i = 0; i < processes; i++)
	{
		sum += buf->data[i].sum;
	}

	printf("Znaleziono %d liczb pierwszych\n", sum);

	return 0;

}