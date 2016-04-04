#include "common.h"
#define FIFO "MyFIFO"

int main() 
{ // Zapis -------------
	int fdes,res,i=0;
	static char c;
	
	printf("Otwieranie pliku %s...\n", FIFO);
	fdes = open(FIFO, O_RDONLY);
	if(fdes < 0)
	{ 
		perror("Open");
		exit(0);
	}
	
	printf("Plik %s otwarty (fd: %d)\n", FIFO, fdes);

	do 
	{
		res = read(fdes, &c, 1);
		printf("Odczyt: %c, wynik: %d\n", c, res);
	} while(res > 0);
	printf("fifo_read: Zamykanie FIFO\n");
	close(fdes);
}
