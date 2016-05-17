#include "producer_consumer.h"

#define REQUIRED_ARGS 3

void usage(void)
{
	printf("consumer [id] [steps]\n");
}

int main(int argc, char** argv)
{
	if(REQUIRED_ARGS != argc)
	{
		usage();
		return 1;
	}

	int size, fd; 
	buffer_t *wbuf;
	fd = shm_open("bufor", O_RDWR|O_CREAT , 0774); 
 	if(fd == -1)
 	{ 
 		perror("open"); 
 		exit(-1); 
 	} 

	wbuf = (buffer_t*) mmap(0, 
						    sizeof(buffer_t), 
						    PROT_READ | PROT_WRITE,
						    MAP_SHARED, 
						    fd, 
						    0); 

	if(wbuf == NULL) 
	{
		perror("map");  
		exit(-1); 
	}

	int id = atoi(argv[1]);
	int steps = atoi(argv[2]);
	int i = 1; 

	for (; i <= steps; i++)
	{
 		sem_wait(&(wbuf->full)); 
 		sem_wait(&(wbuf->mutex));
 		printf("Odebrano: \"%s\"\n", wbuf->buffer[wbuf->head]);
 		printf("head: %d, tail: %d, count: %d\n", wbuf->head, wbuf->tail, wbuf->count);
 		wbuf->count--; 
 		wbuf->tail = (wbuf->tail +1) % BSIZE; 
 		sem_post(&(wbuf->mutex)); 
 		sem_post(&(wbuf->empty)); 
 		sleep(1); 
	}

	printf("Konsument %d: Koniec\n", id);
	return 0;
}
 
