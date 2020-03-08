#pragma once
#include <string.h>

#define true 1
#define false 0

typedef struct {
	char name[50];
	size_t name_length;
	char producator[50];
	size_t prod_length;
}m_prim;

m_prim create(char* name, char* producator);

