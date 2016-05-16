#include "producer_consumer.h"

#define REQUIRED_ARGS 3

void usage(void)
{
	printf("producer [id] [steps]\n");
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
		sem_wait(&(wbuf->empty)); 
		sem_wait(&(wbuf->mutex));
		sprintf(wbuf->buffer[wbuf->head], "Producent %d, krok %d/%d\n", id, i, steps);
		printf("Producent %d, krok %d/%d\n", id, i, steps);
		wbuf->count++;
		wbuf->head = (wbuf->head +1) % BSIZE;
    	sem_post(&(wbuf->mutex)); 
    	sem_post(&(wbuf->full)); 
    	sleep(1); 
	}

	printf("Producent %d: Koniec\n", id);
	return 0;
}
 
