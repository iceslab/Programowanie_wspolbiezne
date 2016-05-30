#include "common.h"


int sendMessage(int s, 
				mms_t* msg, 
				int blen, 
				struct sockaddr * adr_serw, 
				unsigned slen)
{
	int snd = sendto(s, msg, blen, 0, adr_serw, slen);
	
	if(snd < 0) 
	{
		perror("sendto()");
		return -1;
	}

	struct sockaddr_in* addr = (struct sockaddr_in*) adr_serw;
	printf("Wyslano komunikat do %s:%d snd %d\nTyp: %d, tresc: \"%s\", fh: %d\n",
			inet_ntoa(addr->sin_addr), 
			ntohs(addr->sin_port),
			snd, 
			msg->type, 
			msg->buffer, 
			msg->fh);
	return 0;
}

int receiveMessage(int s, 
					mms_t* msg, 
					int blen, 
					struct sockaddr * adr_serw, 
					unsigned slen)
{
	memset((char *) msg, '\0', sizeof(mms_t));
	int rec = recvfrom(s, msg, blen, 0, adr_serw, &slen);
	if(rec < 0)
	{
		perror("recvfrom()");
		return -1;
	} 


	struct sockaddr_in* addr = (struct sockaddr_in*) adr_serw;

	printf("Odebrano komunikat z %s:%d res %d\n Typ: %d, tresc: \"%s\", fh: %d\n",
			inet_ntoa(addr->sin_addr), 
			ntohs(addr->sin_port),
			rec, 
			msg->type, 
			msg->buffer, 
			msg->fh);

	return 0;
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Za malo argumentow\n");
		return -1;
	}	

	struct sockaddr_in adr_moj, adr_serw;
	int s, i, snd, rec, blen = sizeof(mms_t);
	unsigned slen = sizeof(adr_serw);
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
	adr_moj.sin_port = htons(PORT_CLI);
	adr_moj.sin_addr.s_addr = htonl(INADDR_ANY);
	
	memset((char *) &adr_serw, 0, sizeof(adr_serw));
	adr_serw.sin_family = AF_INET;
	adr_serw.sin_port = htons(PORT);
	if (inet_aton(argv[1], &adr_serw.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		return -1;
	}


	if (bind(s,(struct sockaddr *) &adr_moj, sizeof(adr_moj)) == -1)
	{
		perror("bind");
		return -1;	
	}

	// Odbior komunikatow
	for (;;) 
	{
		// Odbior polecenia
		char message[SIZE] = {'\0'};
		printf(">: ");
		scanf("%s", message);
		message[SIZE - 1] = '\0';

		// Interpretacja komendy
		if(!strcmp(message, "openr"))
		{
			msg.type = OPENR;

			printf("Podaj nazwe pliku >: ");
			scanf("%s", msg.buffer);

			msg.count = strlen(msg.buffer);
			msg.fh = -1;

			sendMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
			receiveMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
		}
		else if(!strcmp(message, "openw"))
		{
			msg.type = OPENW;

			printf("Podaj nazwe pliku >: ");
			scanf("%s", msg.buffer);

			msg.count = strlen(msg.buffer);
			msg.fh = -1;

			sendMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
			receiveMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
		}
		else if(!strcmp(message, "read"))
		{
			msg.type = READ;

			printf("Podaj numer deskryptora >: ");
			scanf("%d", &msg.fh);

			printf("Podaj ilosc bajtow >: ");
			scanf("%d", &msg.count);

			memset(msg.buffer, '\0', SIZE);

			sendMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
			receiveMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
		}
		else if(!strcmp(message, "close"))
		{
			msg.type = CLOSE;
			msg.count = 0;
			
			printf("Podaj numer deskryptora >: ");
			scanf("%d", &msg.fh);
			
			memset(msg.buffer, '\0', SIZE);

			sendMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
			receiveMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
		}
		else if(!strcmp(message, "write"))
		{
			msg.type = WRITE;

			printf("Podaj numer deskryptora >: ");
			scanf("%d", &msg.fh);

			printf("Podaj dane >: ");
			
			memset(msg.buffer, '\0', SIZE);
			scanf("%s", msg.buffer);
			msg.buffer[SIZE - 1] = '\0';

			
			msg.count = strlen(msg.buffer);

			sendMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
			receiveMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
		}
		else if(!strcmp(message, "stop"))
		{
			msg.type = STOP;
			msg.count = 0;
			msg.fh = -1;
			memset(msg.buffer, '\0', SIZE);

			sendMessage(s, &msg, blen, (struct sockaddr *) &adr_serw, slen);
		}
		else if(!strcmp(message, "exit"))
		{
			printf("Zamykanie klienta\n");
			break;
		}
		else
		{
			printf("Nieznana komenda\n");
			printf("Znane komendy: openr, openw, close, read, write, stop, exit\n");
		}
	}
	close(s);
	return 0;

}