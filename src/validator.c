#include "validator.h"

int validate_string(const char* str)
{
	return strlen(str) == 0;
}

int validate_quantity(const int q)
{
	return q <= 0;
}