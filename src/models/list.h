#pragma once
#include <string.h>
#include <stdlib.h>
#include "model.h"

/*
	Reprezentarea listei de materii prime ca un tip de date
*/
typedef struct {
	MatPrim** matPrim;
	size_t length;
	size_t size;
}ListMP;

//Constructor pentru lista de materii prime
ListMP l_create();

/*
	Functie care se ocupa de eliberarea memoriei alocate de o lista de materii prime
*/
void destroyListMP(ListMP* limp);

/*
	Adauga in lista "limp" o materie prima "matPrim"
*/
void l_add(ListMP* limp, MatPrim* matPrim);

/*
	Functie care sterge un element de la o pozitie data
*/
int l_del(ListMP* limp, int position);