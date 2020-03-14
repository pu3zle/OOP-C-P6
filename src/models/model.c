#include "model.h"
#pragma warning(disable:4996)

m_prim create(char* name, char* producator, size_t quantity)
{
	m_prim matPrim;

	size_t nL = strlen(name);
	matPrim.name_length = nL;
	matPrim.name = (char*)new(nL+1);
	strncpy(matPrim.name, name, nL);
	matPrim.name[nL] = '\0';

	size_t pL = strlen(producator);
	matPrim.prod_length = pL;
	matPrim.producator = (char*)new(pL+1);
	strncpy(matPrim.producator, producator, pL);
	matPrim.producator[pL] = '\0';

	matPrim.quantity = quantity;
	return matPrim;
}

void set_name(m_prim* matPrim, char* name)
{
	size_t n = strlen(name);
	delete(matPrim->name, matPrim->name_length + 1);

	matPrim->name = (char*)new(n + 1);
	strcpy(matPrim->name, name);

	matPrim->name[n] = '\0';
	matPrim->name_length = n;
}

void set_prod(m_prim* matPrim, char* prod)
{
	size_t n = strlen(prod);
	delete(matPrim->producator, matPrim->prod_length + 1);

	matPrim->producator = (char*)new(n + 1);
	strcpy(matPrim->producator, prod);
	
	matPrim->producator[n] = '\0';
	matPrim->prod_length = n;
}

void set_quantity(m_prim* matPrim, int q)
{
	matPrim->quantity = q;
}

ListMP l_create()
{
	ListMP limp;
	limp.length = 0;
	return limp;
}


