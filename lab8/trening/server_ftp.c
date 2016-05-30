#include "common.h"

int main(int argc, char *argv[])
{
	struct sockaddr_in adr_moj, adr_cli;
	int s, i, snd, rec, blen = sizeof(mms_t);
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
	if (bind(s,(struct sockaddr *) &adr_moj, sizeof(adr_moj)) == -1)
	{
		perror("bind");
		return -1;	
	}

	// Odbior komunikatow
	for (;;) 
	{
		rec = recvfrom(s, &msg, blen, 0,(struct sockaddr *) &adr_cli, &slen);
		if(rec < 0)
		{
			perror("recvfrom()");
			return -1;
		} 

		printf("Odebrano komunikat z %s:%d res %d\n Typ: %d %s\n",
				inet_ntoa(adr_cli.sin_addr), 
				ntohs(adr_cli.sin_port),
				rec, 
				msg.type, 
				msg.buffer);
		
		// Odpowiedz
		sprintf(msg.buffer,"Odpowiedz %d",i);
		snd = sendto(s, &msg, blen, 0,(struct sockaddr *) &adr_cli, slen);
		
		if(snd < 0) 
		{
			perror("sendto()");
			return 0;
		}

		printf("wyslano odpowiedz -res %d\n",snd);
	}
	close(s);
	return 0;

}