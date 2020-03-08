#include "model.h"
#pragma warning(disable:4996)

m_prim create(char* name, char* producator, size_t quantity)
{
	m_prim matPrim;
	size_t nL = strlen(name);
	matPrim.name_length = nL;
	strncpy(matPrim.name, name, nL);

	size_t pL = strlen(producator);
	matPrim.prod_length = pL;
	strncpy(matPrim.producator, producator, pL);

	matPrim.quantity = quantity;
	return matPrim;
}

ListMP l_create()
{
	ListMP limp;
	limp.length = 0;
	return limp;
}
