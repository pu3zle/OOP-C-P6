#pragma once
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

/*
	Reprezentarea materiei prime ca un tip de date
*/
typedef struct {
	char* name;
	size_t name_length;
	
	char* provider;
	size_t provider_length;

	size_t quantity;
}MatPrim;



//Constructor pentru materii prime
MatPrim* MatPrimCreate(char* name, char* provider, size_t quantity);

//Set-ere pentru field-urile materiei prime
void set_name(MatPrim* matPrim, char* name);
void set_provider(MatPrim* matPrim, char* provider);
void set_quantity(MatPrim* matPrim, int q);

/*
	Functie care se ocupa cu eliberarea memoriei alocate de o materie prima
	Params: o materie prima
*/
void destroyM_Prim(MatPrim* matPrim);

/*
	Functie care copiaza informatiile dintr-o materie prima (m1) in alta materie prima (m2)
*/
void CpyLimp(MatPrim* m1, MatPrim* m2);

/*
	Functie care rezerva un spatiu "NewSize" pentru o materie prima "mat_prim" cu "Length" elemente
*/
void ReserveNewMatPrim(MatPrim*** mat_prim, size_t NewSize, size_t Length);

