#include "common.h" 

#define COMMAND "ps -ef"
#define COMMUNICATION_TYPE "r"
#define SORT -1

struct process_info
{
	char uid[SMALL_BUFFER_LENGTH]; 
	char pid[SMALL_BUFFER_LENGTH];
	char ppid[SMALL_BUFFER_LENGTH];
	char c[SMALL_BUFFER_LENGTH];
	char stime[SMALL_BUFFER_LENGTH];
	char tty[SMALL_BUFFER_LENGTH];
	char time_str[SMALL_BUFFER_LENGTH];
	char cmd[MAX_BUFFER_LENGTH];
};

int comp (const void * elem1, const void * elem2);

int main(int argc, char** argv)
{
	FILE* stream = popen(COMMAND, COMMUNICATION_TYPE);

	struct process_info piArray[MAX_PROCESSES] = {0};

	if(NULL != stream)
	{
		int result = 0;

		// Bufory tymczasowe na informacje
		char uid[SMALL_BUFFER_LENGTH]; 
		char pid[SMALL_BUFFER_LENGTH];
		char ppid[SMALL_BUFFER_LENGTH];
		char c[SMALL_BUFFER_LENGTH];
		char stime[SMALL_BUFFER_LENGTH];
		char tty[SMALL_BUFFER_LENGTH];
		char time_str[SMALL_BUFFER_LENGTH];
		char cmd[MAX_BUFFER_LENGTH];
		
		result = fscanf(stream, 
						"%s %s %s %s %s %s %s %s", 
						uid, 
						pid, 
						ppid, 
						c, 
						stime, 
						tty, 
						time_str,
						cmd);
		int i = 0;
		for(i = 0; i < MAX_PROCESSES; ++i)
		{
			// Czyta wszystkie parametry jako stringi, 
			// a ostatni aż do końca linii
			result = fscanf(stream, 
						"%s %s %s %s %s %s %s %[^\n]s", 
						uid, 
						pid, 
						ppid, 
						c, 
						stime, 
						tty, 
						time_str,
						cmd);
			if(EOF == result)
				break;

			strcpy(piArray[i].uid, uid);
			strcpy(piArray[i].pid, pid);
			strcpy(piArray[i].ppid, ppid);
			strcpy(piArray[i].c, c);
			strcpy(piArray[i].stime, stime);
			strcpy(piArray[i].tty, tty);
			strcpy(piArray[i].time_str, time_str);
			strcpy(piArray[i].cmd, cmd);

		}
		
		qsort(piArray, i, sizeof(struct process_info), comp);

		printf("Odczytano %d/%d procesów:\n", i, MAX_PROCESSES);
		int j = 0;
		for(; j < i; ++j)
		{
			printf("%s %s %s %s %s %s %s %s\n", 
				   piArray[j].uid, 
				   piArray[j].pid, 
				   piArray[j].ppid, 
				   piArray[j].c, 
				   piArray[j].stime, 
				   piArray[j].tty, 
				   piArray[j].time_str,
				   piArray[j].cmd);
		}
		pclose(stream);
	}
	else
	{
		perror("Nie można utworzyć strumienia");
	}

	return 0;
}

int comp (const void * elem1, const void * elem2) 
{
    struct process_info* f = (struct process_info*)elem1;
    struct process_info* s = (struct process_info*)elem2;
    return SORT * strcmp((*f).time_str, (*s).time_str);
}