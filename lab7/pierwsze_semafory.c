#include "primes_utils.h" 

#define REQUIRED_ARGC 4
#define BUF_SIZE 512
#define BSIZE 5

typedef struct
{
	int begin;
	int end;
	int sum;
} data_t;

typedef struct
{
	int head;
	int tail;
	int count;
	sem_t mutex;
	sem_t empty;
	sem_t full;
	data_t buffer[BSIZE];
} buf_t;

// typedef struct
// {
// 	int dimension;
// 	data_t data[BUF_SIZE];
// } buf_t;

void usage(void)
{
	printf("pierwsze_semafory [begin] [end] [processes]\n");
}

int main(int argc, char** argv)
{
	timespec_t timeStart = {0, 0}, timeEnd = {0, 0};
	clock_gettime(CLOCK_BOOTTIME, &timeStart);
	if(REQUIRED_ARGC != argc)
	{
		usage();
		return 1;
	}

	int fd = shm_open("pierwsze_bufor", O_RDWR|O_CREAT , 0774); 
 	if(fd == -1)
 	{ 
 		perror("shm_open"); 
 		exit(-1); 
 	} 

 	int size = ftruncate(fd, sizeof(buf_t));   
 	if(size < 0) 
	{
		perror("trunc"); 
		exit(-1); 
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

	if(sem_init(&(buf->mutex), 1, 1))
	{ 
		perror("mutex");
		exit(0);  
	}

	if(sem_init(&(buf->empty), 1, BSIZE)) 
	{  
		perror("empty"); 
		exit(0);  
	} 

	if(sem_init(&(buf->full), 1, 0)) 
	{  
		perror("full"); 
		exit(0);  
	} 

	int begin = atoi(argv[1]);
	int end = atoi(argv[2]) + 1;
	int processes = atoi(argv[3]);

	if(processes < 1)
	{
		printf("Za mała liczba procesów (%d) przyjęto 1\n", processes);
		processes = 1;
	}

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
			sem_wait(&(buf->empty)); 
			sem_wait(&(buf->mutex));
			buf->buffer[buf->head].begin = proc_begin;
			buf->buffer[buf->head].end = proc_end;
			buf->buffer[buf->head].sum = primes(proc_begin, proc_end);
			printf("head: %d, tail: %d, count: %d\n", buf->head, buf->tail, buf->count);
			buf->count++;
			buf->head = (buf->head +1) % BSIZE;
	    	sem_post(&(buf->mutex)); 
	    	sem_post(&(buf->full)); 

			// buf->data[i].begin = proc_begin;
			// buf->data[i].end = proc_end;
			// buf->data[i].sum = primes(proc_begin, proc_end);
			exit(0);
		}
		// Macierzysty blad
		else if(0 > forkResult)
		{
			perror("fork");
			--successfull_processes;
		}
	}

	int sum = 0;
	for(i = 0; i < successfull_processes; i++)
	{
		sem_wait(&(buf->full)); 
 		sem_wait(&(buf->mutex));
 		printf("head: %d, tail: %d, count: %d\n", buf->head, buf->tail, buf->count);

		sum += buf->buffer[buf->tail].sum;
 		// for(; j < 3; j++)
 		// 	printf("Zawartosc %d: \"%s\"\n", j, wbuf->buffer[j]);
 		buf->count--; 
 		buf->tail = (buf->tail +1) % BSIZE; 
 		sem_post(&(buf->mutex)); 
 		sem_post(&(buf->empty)); 
	}

	int status = 0, pid = 0;
	// Czekanie na procesy
	for(i = 0; i < successfull_processes; i++)
	{
		pid = wait(&status);
	}

	
    // Sumowanie wynikow
	// for(i = 0; i < processes; i++)
	// {
	// 	sum += buf->data[i].sum;
	// }
	
	clock_gettime(CLOCK_BOOTTIME, &timeEnd);
	timespec_t resultTime = diff(timeStart, timeEnd);
	printf("Znaleziono %d liczb pierwszych w %ld.%ld sekund\n", sum, resultTime.tv_sec, resultTime.tv_nsec);
	munmap(buf, sizeof(buf_t));
	shm_unlink("pierwsze_bufor"); 

	return 0;

}