/*
6. Cofetarie

Creati o aplicatie modulara in C.
Se cere interfata utilizator de tip consola.
Datele introduse de utilizator trebuie validate.
Folositi arhitectura stratificata.
Folositi dezvoltare dirijata de teste (Test Driven Development)
Fiecare metoda din aplicatie trebuie specificata si testata.
Implementati vector dinamic pentru lucru cu liste:
	- in prima saptamana puteti folosi reprezentarea cu un struct ( un vector static si lungime in el)
	- pana in saptamana 2 trebuie folosit alocare dinamica (sa acomodeze oricate elemente)


Creati o aplicatie care permite gestiunea stocului de materii prime folosite intr-o cofetarie.
Fiecare materie prima din stoc are un nume unic, un producator si cantitate.
Aplicatia permite:
1) adaugare de materie prima (daca exista deja in stoc se actualizeaza cantitatea)
2) modificare materie prima 
3) stergere  materie prima
4) Vizualizare materii prime care satisfac un criteriu (nume incepe cu o litera data, cantitatea disponibila e mai mica decat un numar dat)
5) Vizualizare materii prime din stoc ordonat dupa nume sau cantitate disponibila (crescator/descrescator)                                 
*/

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h> 
#include "ui/ui.h"
#include <stdlib.h>

typedef struct {

	size_t TotalAllocated;
	size_t TotalFreed;

}AllocMaster;


AllocMaster s_AllocMaster;

void* new(size_t size)
{
	s_AllocMaster.TotalAllocated += size;

	return malloc(size);
}

void delete(void* memory, size_t size)
{
	s_AllocMaster.TotalFreed += size;

	free(memory);
}


void PrintCurrentUsage()
{
	size_t currentUsage = s_AllocMaster.TotalAllocated - s_AllocMaster.TotalFreed;
	printf("There are currently %llu bytes of memory in use!\n", currentUsage);
}

void destroy(ListMP* limp)
{
	for (size_t i = 0; i < limp->length; i++)
	{
		delete(limp->matPrim[i].name, limp->matPrim[i].name_length+1);
		delete(limp->matPrim[i].producator, limp->matPrim[i].prod_length+1);
	}

}

int main()
{
	s_AllocMaster.TotalAllocated = 0;
	s_AllocMaster.TotalFreed = 0;

	ListMP limp = l_create();
	run(&limp);
	destroy(&limp);
	PrintCurrentUsage();
	_CrtDumpMemoryLeaks();
	return 0;
}
