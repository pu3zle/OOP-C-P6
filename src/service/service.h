#pragma once
#include "..\models\model.h"
#include "..\models\list.h"
#include "..\validator\validator.h"

/*
	Functie care creeaza o materie prima folosind "nume", "provider" si "quantity"
	Si apoi o adauga in lista de materii prime "limp"
	Daca nu este suficient spatiu, aloca mai mult spatiu dinamic.
*/
int add(ListMP* limp, char* name, char* provider, int quantity);

/*
	Functie care verifica daca o materie prima cu numele "name" este deja in lista "limp"
	Params: limp - lista de materii prime
			name - string
*/
int validate_unique(const ListMP* limp, char* name);

/*
	Functia cauta in lista de materii prime "limp" materia prima cu numele "name"
	Daca o gaseste, ii returneaza pozitia
	Altfel, returneaza -1
*/
int search(ListMP* limp, char* name);

/*
	Functie care modifica un atribut al materiei prime in functie de parametrul "op"
	Params: limp - lista materii prime, 
			name - numele materiei prime, 
			modify - cu ce va fi inlocuit atributul materiei prime, 
			op - ce atribut va fi inlocuit:
				-> 0 - numele
				-> 1 - producatorul
				-> 2 - cantitatea

*/
int modify(ListMP* limp, char* name, char* modify, int op);

/*
	Functie care sterge din lista de materii prime o materie prima cu numele "name"
	Params: limp - lista de materii prime, name - numele materiei prime care trebuie stearsa
*/
int del(ListMP* limp, char* name);

/*
	Functie ajutatoare care transforma un string (care reprezinta un numar intreg) intr-un intreg si il returneaza
*/
int char2int(char* q);

/*
	Functie care sorteaza lista de materii prime dupa o functie de comparare
*/
int sort(ListMP* limp, int reverse, int(*Comparison)(MatPrim*, MatPrim*));

int QuantityComparison(MatPrim* a, MatPrim* b);

int NameComparison(MatPrim* a, MatPrim* b);



