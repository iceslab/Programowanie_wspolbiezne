#include "common.h"


int sendMessage(int s, 
				mms_t* msg, 
				int blen, 
				struct sockaddr * adr_cli, 
				unsigned slen)
{
	int snd = sendto(s, msg, blen, 0, adr_cli, slen);
	
	if(snd < 0) 
	{
		perror("sendto()");
		return -1;
	}

	struct sockaddr_in* addr = (struct sockaddr_in*) adr_cli;
	printf("Wyslano komunikat do %s:%d snd %d\nTyp: %d, tresc: \"%s\"\n",
			inet_ntoa(addr->sin_addr), 
			ntohs(addr->sin_port),
			snd, 
			msg->type, 
			msg->buffer);
	return 0;
}

int receiveMessage(int s, 
					mms_t* msg, 
					int blen, 
					struct sockaddr * adr_cli, 
					unsigned slen)
{
	memset((char *) msg, '\0', sizeof(mms_t));
	int rec = recvfrom(s, msg, blen, 0, adr_cli, &slen);
	if(rec < 0)
	{
		perror("recvfrom()");
		return -1;
	} 


	struct sockaddr_in* addr = (struct sockaddr_in*) adr_cli;

	printf("Odebrano komunikat z %s:%d res %d\n Typ: %d %s\n",
			inet_ntoa(addr->sin_addr), 
			ntohs(addr->sin_port),
			rec, 
			msg->type, 
			msg->buffer);

	return 0;
}

int main(int argc, char *argv[])
{
	struct sockaddr_in adr_moj, adr_cli;
	int s, i, snd, rec, blen = sizeof(mms_t);
	int run = 1;
	unsigned slen = sizeof(adr_cli);
	char buf[SIZE];
	mms_t msg;
	
	gethostname(buf, sizeof(buf));
	printf("Host: %s\n",buf);
	
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if(s < 0)
	{
		perror("socket");
		return -1;
	} 

	printf("Gniazdko %d utworzone\n",s);
	
	// Ustalenie adresu IP nadawcy
	memset((char *) &adr_moj, 0, sizeof(adr_moj));
	adr_moj.sin_family = AF_INET;
	adr_moj.sin_port = htons(PORT);
	adr_moj.sin_addr.s_addr = htonl(INADDR_ANY);
	
	memset((char *) &adr_cli, 0, sizeof(adr_cli));
	// adr_cli.sin_family = AF_INET;
	// adr_cli.sin_port = htons(PORT);
	// if (inet_aton(argv[1], &adr_cli.sin_addr)==0) {
	// 	fprintf(stderr, "inet_aton() failed\n");
	// 	return -1;
	// }


	if (bind(s,(struct sockaddr *) &adr_moj, sizeof(adr_moj)) == -1)
	{
		perror("bind");
		return -1;	
	}

	// Odbior komunikatow
	while (run) 
	{
		// Odbior polecenia
		// char message[SIZE] = {'\0'};
		// printf(">: ");
		// scanf("%s", message);
		// message[SIZE - 1] = '\0';

		receiveMessage(s, &msg, blen, (struct sockaddr *) &adr_cli, slen);
		int result = 0;
		// Interpretacja komendy
		switch(msg.type)
		{
			case OPENR:
				printf("open O_RDONLY - nazwa: \"%s\"\n", msg.buffer);
				msg.fh = open(msg.buffer, O_RDONLY);
				printf("Deskryptor pliku: %d\n", msg.fh);
				// typedef struct 
				// {
				// 	int type;
				// 	int count;
				// 	int fh;
				// 	char buffer[SIZE];
				// } mms_t;
				sendMessage(s, &msg, blen, (struct sockaddr *) &adr_cli, slen);
				break;
			case OPENW:
				printf("open O_WRONLY - nazwa: \"%s\"\n", msg.buffer);
				msg.fh = open(msg.buffer, O_WRONLY);
				printf("Deskryptor pliku: %d\n", msg.fh);
				sendMessage(s, &msg, blen, (struct sockaddr *) &adr_cli, slen);
				break;
			case READ:
				printf("read - fd: %d, count: %d\n", msg.fh, msg.count);
				msg.count = read(msg.fh, msg.buffer, msg.count);
				printf("Odczytano: %d bajtow\n", msg.count);
				sendMessage(s, &msg, blen, (struct sockaddr *) &adr_cli, slen);
				break;
			case CLOSE:
				printf("close - fh: %d\n", msg.fh);
				result = close(msg.fh);
				printf("Wynik: %d\n", result);
				sendMessage(s, &msg, blen, (struct sockaddr *) &adr_cli, slen);
				break;
			case WRITE:
				printf("write - fd: %d, count: %d\n", msg.fh, msg.count);
				msg.count = write(msg.fh, msg.buffer, msg.count);
				printf("Zapisano: %d bajtow\n", msg.count);
				sendMessage(s, &msg, blen, (struct sockaddr *) &adr_cli, slen);
				break;
			case STOP:
				printf("Zamykanie serwera\n");
				run = 0;
				break;
			default:
				printf("Nieznana komenda\n");
				break;
			
		}
	}
	close(s);
	return 0;

}