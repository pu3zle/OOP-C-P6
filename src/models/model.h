#pragma once
#include <string.h>
#include <stdlib.h>

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
}MatPrim;


typedef struct {
	MatPrim matPrim[100];
	size_t length;
}ListMP;

ListMP l_create();

//void l_add(ListMP* limp, m_prim* matPrim);
MatPrim MatPrimCreate(char* name, char* producator, size_t quantity);

void set_name(MatPrim* matPrim, char* name);
void set_prod(MatPrim* matPrim, char* prod);
void set_quantity(MatPrim* matPrim, int q);

void destroyM_Prim(MatPrim* matPrim);

void destroyListMP(ListMP* limp);

void CpyLimp(MatPrim* m1, MatPrim* m2);



