#include "common.h" 

#define TRUE 1
#define FALSE 0
#define PLACES 8   
// Liczba wolnych miejsc w czytelni 
sem_t wolne ;    // Liczba wolnych miejsc w czytelni 
sem_t wr;       // Kontrola dostępu do czytelni

void Reader() 
{ 
	while (TRUE) 
	{            
		sem_wait(&wolne);    // Czekanie na miejsca w czytelni 
		read_db();          // Czytelnik w czytelni - czyta
		sem_post(&wolne);    // Zwolnienie miejsca w czytelni 
	} 
}

void Writer() 
{ 
	int i = 0;
	while (TRUE) 
	{                
		create_data(); 	// Pisarz zastanawia się
		sem_wait(wr);	// Zablokowanie dostępu dla pisarzy 
		// Wypieranie czytelników z czytelni  
		for(i = 1; i <= PLACES; i++) 
		{
			sem_wait(&wolne);
		}
		write_db();		// Pisarz w czytelni – pisze 
		
		// Wpuszczenie czytelników
		for(i = 1; i <= PLACES; i++) 
		{
			sem_post(&wolne);
		}
		sem_post(wr);	// Odblokowanie pisarzy
	} 
} 

int main(int argc, char** argv)  
{ 
	sem_init(wolne,PLACES); 
	sem_init(wr, 1); 
}