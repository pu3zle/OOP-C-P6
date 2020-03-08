#include "validator.h"

int validate_string(char* str)
{
	return strlen(str) != 0;
}

int validate_quantity(int q)
{
	return q >= 0;
}