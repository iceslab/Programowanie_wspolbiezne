#include "producer_consumer.h"

int main(int argc, char** argv)
{
	int size, fd; 
	buffer_t *wbuf; 
 	shm_unlink("bufor"); 
 	fd = shm_open("bufor", O_RDWR|O_CREAT , 0774); 
 	if(fd == -1)
 	{ 
 		perror("open"); 
 		exit(-1); 
 	} 

 	size = ftruncate(fd, sizeof(buffer_t));   
 	if(size < 0) 
	{
		perror("trunc"); 
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
	
	// Inicjacja obszaru
	wbuf->count = 0; 
	wbuf->head = 0; 
	wbuf->tail = 0; 

	if(sem_init(&(wbuf->mutex), 1, 1))
	{ 
		perror("mutex");
		exit(0);  
	}

	if(sem_init(&(wbuf->empty), 1, BSIZE)) 
	{  
		perror("empty"); 
		exit(0);  
	} 

	if(sem_init(&(wbuf->full), 1, 0)) 
	{  
		perror("full"); 
		exit(0);  
	} 

	printf("Zainicjowano pamięć\n");

	return 0;
}
