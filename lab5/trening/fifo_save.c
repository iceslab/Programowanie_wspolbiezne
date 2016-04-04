#include "common.h"
#define FIFO "MyFIFO"

int main() 
{ // Zapis -------------
	int fdes,res,i=0;
	static char c;
	res = mkfifo(FIFO,0666);
	if(res < 0) 
	{ 
		perror("mkfifo"); 
	}
	
	printf("mkfifo - wynik %d\n",res);
	fdes = open(FIFO, O_RDWR);
	if(fdes < 0)
	{ 
		perror("Open");
		exit(0);
	}
	
	do 
	{
		c = '0' + (i++)%10;
		printf("Zapis: %c \n", c);
		res = write(fdes, &c, 1);
	} while(i < 10);
	printf("fifo_save: Zamykanie FIFO\n");
	close(fdes);
}
