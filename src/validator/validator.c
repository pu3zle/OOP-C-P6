#include "validator.h"

int validate_string(const char* str)
{
	char* ptr = strtok((char*)str, (const char*)" ");
	return (ptr == NULL);
}

int validate_quantity(const int q)
{
	return q <= 0;
}
