#pragma once
#include <string.h>

#define true 1
#define false 0

extern void* new(size_t size);

extern void delete(void* memory, size_t size);

typedef struct {
	char* name;
	size_t name_length;
	
	char* producator;
	size_t prod_length;

	size_t quantity;
}m_prim;


typedef struct {
	m_prim matPrim[100];
	size_t length;
}ListMP;

ListMP l_create();

//void l_add(ListMP* limp, m_prim* matPrim);
m_prim create(char* name, char* producator, size_t quantity);

void set_name(m_prim* matPrim, char* name);
void set_prod(m_prim* matPrim, char* prod);
void set_quantity(m_prim* matPrim, int q);




