#pragma once
#include <string.h>
#pragma warning(disable:4996)

/*
	Functie care valideaza daca un string este gol
	Params: str - string
*/
int validate_string(const char* str);


/*
	Functie care valideaza daca un numar poate sa fie cantitate (sa nu fie negativ)
*/
int validate_quantity(const int q);
