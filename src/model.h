#pragma once
#include <string.h>

#define true 1
#define false 0

typedef struct {
	char name[50];
	size_t name_length;

	char producator[50];
	size_t prod_length;

	size_t quantity;
}m_prim;


typedef struct {
	m_prim matPrim[100];
	size_t length;
}ListMP;

ListMP l_create();

m_prim create(const char* name, const char* producator, const size_t quantity);

