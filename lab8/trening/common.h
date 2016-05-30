#define OPENR 1 // Otwarcie pliku do odczytu
#define OPENW 2 // Otwarcie pliku do zapisu
#define READ 3  // Odczyt fragmentu pliku
#define CLOSE 4 // Zamkniecie pliku
#define WRITE 5 // Zapis fragmentu pliku
#define STOP 10 // Zatrzymanie serwera

#define SIZE 512
#define PORT 9950
#define PORT_CLI 9951
#define SRV_IP "127.0.0.1"

#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>



typedef struct 
{
	int type;
	int count;
	int fh;
	char buffer[SIZE];
} mms_t;