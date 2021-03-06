#include "primes_utils.h"

void createSubprocesses(int processes, 
						char* subprocessName, 
						int* successfull_processes);
void createOrders(int begin, 
				  int end, 
				  int processes, 
				  mqd_t* mq,
				  int subParts);

int main(int argc, char** argv)
{
	if(argc == 5) 
	{
		unlinkQueues();
		int begin = atoi(argv[1]);
		int end = atoi(argv[2]);
		int processes = atoi(argv[3]);
		int subParts = atoi(argv[4]);
		int successfull_processes = 0;
		time_t start_time = time(NULL);

		mqd_t queue_in, queue_out;

		if(!makeQueues(&queue_in, 
					   &queue_out, 
					   O_RDWR | O_CREAT))
		{
			printf("Nie udało się utworzyć kolejki\n");
			exit(0);
		}
		
		char* subprocessName = NULL;
		getSubprocessName(&subprocessName, 
						  argv[0], 
						  SUBPROCESS_POSIX_BALANCED_NAME);

		// Tworzenie procesów
		createSubprocesses(processes, 
						   subprocessName, 
						   &successfull_processes);
		// Tworzenie zadań
		//createOrders(begin, end, successfull_processes, &queue_in, subParts);
		releaseSubprocessName(&subprocessName);

		msg_t order;
		int proc_begin, proc_end = begin;
		int proc_number = 0;
		int proc_primes = 0;
		int primes = 0;
		unsigned priority = 0;
		int i = 0;
		printf("subParts: %d\n", subParts);
		for(; i < subParts; ++i)
		{
			proc_begin = proc_end;
			proc_end = (((i + 1) / (float)subParts) * (end - begin)) + begin;

			msg_t order = {i, 
						   proc_begin, 
						   proc_end, 
						   proc_end - proc_begin};
		   	mq_send(queue_in, (char*)&order, sizeof(msg_t), 2);
		   	// printf("%d %d %d %d\n", order.number, order.begin, order.end, order.count);
			mq_receive(queue_out, (char*)&order, sizeof(msg_t), &priority);
			primes += order.count;
		}
	
		for(int i = 0; i < processes; ++i)
		{
			msg_t order = {-1, 
						   -1, 
						   -1, 
						   -1};
			// printf("%d %d %d %d\n", order.number, order.begin, order.end, order.count);
			mq_send(queue_in, (char*)&order, sizeof(msg_t), 1);
		}
		// Czekanie na procesy
		int status, pid;
		for(int i = 0; i < successfull_processes; ++i)
		{
			pid = wait(&status);
			printf("Proces %d zakończony\n", pid);
		}

		releaseQueues(&queue_in, &queue_out);
		unlinkQueues();

		start_time = time(NULL) - start_time;
		printf("Liczb pierwszych: %d, czas trwania: %ld s\n", 
			   primes, 
			   start_time);
	}	
	else
	{
		printf("Usage: pierwsze [begin] [end] [processes] [subParts]\n");
	}

	return 0;
}

void createSubprocesses(int processes, 
						char* subprocessName, 
						int* successfull_processes)
{
	*successfull_processes = processes;
	// Tworzenie procesów
	for(int i = 1; i <= processes; ++i)
	{
		if(fork() == 0)
		{
			// Podmienianie obrazu w pamięci
			execl(subprocessName, 
				  subprocessName, 
				  NULL);
			perror("Nie udało się utworzyć procesu");
			--(*successfull_processes);
			exit(0);
		}
	}
}

void createOrders(int begin, 
				  int end, 
				  int processes, 
				  mqd_t* mq,
				  int subParts)
{
	int proc_begin, proc_end = begin;
	// Zapełnianie kolejki
	for(int i = 1; i <= subParts; ++i)
	{
		proc_begin = proc_end;
		proc_end = ((i / (float)subParts) * (end - begin)) + begin;

		msg_t order = {i, 
					   proc_begin, 
					   proc_end, 
					   proc_end - proc_begin};
	   	mq_send(*mq, (char*)&order, sizeof(msg_t), 2);
	   	printf("%d %d %d %d\n", order.number, order.begin, order.end, order.count);
	}

	printf("processes: %d\n", processes);
	for(int i = 0; i < processes; ++i)
	{
		msg_t order = {-1, 
					   -1, 
					   -1, 
					   -1};
		printf("%d %d %d %d\n", order.number, order.begin, order.end, order.count);
		printf("Macierzysty %d: Wysyłanie\n", 
			   getpid());
		mq_send(*mq, (char*)&order, sizeof(msg_t), 1);
		printf("Macierzysty %d: Wysłano\n", 
				getpid());
	}
}

