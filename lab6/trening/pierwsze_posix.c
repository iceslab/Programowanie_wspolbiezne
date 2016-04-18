#include "primes_utils.h"

void createSubprocesses(int processes, 
						char* subprocessName, 
						int* successfull_processes);
void createOrders(int begin, 
				  int end, 
				  int processes, 
				  mqd_t* mq);

int main(int argc, char** argv)
{
	if(argc == 4) 
	{
		int begin = atoi(argv[1]);
		int end = atoi(argv[2]);
		int processes = atoi(argv[3]);
		int successfull_processes = 0;
		time_t start_time = time(NULL);



		mqd_t queue_in, queue_out;
		struct mq_attr attr_in, attr_out;

		makeQueues(&queue_in, &queue_out);

		if(MQ_ERROR == queue_in || MQ_ERROR == queue_out)
		{
			perror("Nie udało się utworzyć kolejki");
			exit(0);
		}
		
		char* subprocessName = NULL;
		getSubprocessName(&subprocessName, 
						  argv[0], 
						  SUBPROCESS_POSIX_NAME);

		// Tworzenie procesów
		createSubprocesses(processes, 
						   subprocessName, 
						   &successfull_processes);
		// Tworzenie zadań
		createOrders(begin, end, processes, &queue_in);
		releaseSubprocessName(&subprocessName);

		msg_t order;
		int proc_number = 0;
		int proc_primes = 0;
		int primes = 0;
		unsigned priority = 0;
		
		for(int i = 0; i < successfull_processes; ++i)
		{
			mq_receive(queue_out, (char*)&order, sizeof(msg_t), &priority);
			primes += order.count;
		}
		
		releaseQueues(&queue_in, &queue_out);
		
		// Czekanie na procesy
		int status, pid;
		for(int i = 0; i < successfull_processes; ++i)
		{
			pid = wait(&status);
			printf("Proces %d zakończony\n", pid);
		}

		start_time = time(NULL) - start_time;
		printf("Liczb pierwszych: %d, czas trwania: %ld s\n", 
			   primes, 
			   start_time);
	}	
	else
	{
		printf("Usage: pierwsze [begin] [end] [processes]\n");
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
				  mqd_t* mq)
{
	int proc_begin, proc_end = begin;
	// Zapełnianie kolejki
	for(int i = 1; i <= processes; ++i)
	{
		proc_begin = proc_end;
		proc_end = ((i / (float)processes) * (end - begin)) + begin;

		msg_t order = {i, 
					   proc_begin, 
					   proc_end, 
					   proc_end - proc_begin};
	   	mq_send(*mq, (char*)&order, sizeof(msg_t), 10);
	   	// printf("Order: number: %d, begin: %d, end: %d, count: %d\n", 
	   	// 	   i, 
	   	// 	   proc_begin, 
	   	// 	   proc_end, 
	   	// 	   proc_end - proc_begin);
	}
}

