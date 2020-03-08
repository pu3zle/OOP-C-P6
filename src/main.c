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
a) adaugare de materie prima (daca exista deja in stoc se actualizeaza cantitatea)
b) modificare materie prima 
c) stergere  materie prima
d) Vizualizare materii prime care satisfac un criteriu (nume incepe cu o litera data, cantitatea disponibila e mai mica decat un numar dat)
e) Vizualizare materii prime din stoc ordonat dupa nume sau cantitate disponibila (crescator/descrescator)
*/

#include "ui.h"

int main()
{
	ListMP limp = l_create();
	run(&limp);
	return 0;
}