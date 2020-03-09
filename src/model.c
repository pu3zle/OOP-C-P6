#include "model.h"
#pragma warning(disable:4996)

m_prim create(const char* name, const char* producator, const size_t quantity)
{
	m_prim matPrim;
	size_t nL = strlen(name);
	matPrim.name_length = nL;
	strncpy(matPrim.name, name, nL);
	matPrim.name[nL] = '\0';

	size_t pL = strlen(producator);
	matPrim.prod_length = pL;
	strncpy(matPrim.producator, producator, pL);
	matPrim.producator[pL] = '\0';

	matPrim.quantity = quantity;
	return matPrim;
}

ListMP l_create()
{
	ListMP limp;
	limp.length = 0;
	return limp;
}

void l_add(ListMP* limp, m_prim* matPrim)
{
	strcpy(limp->matPrim[limp->length].name, matPrim->name);
	strcpy(limp->matPrim[limp->length].producator, matPrim->producator);
	limp->matPrim[limp->length].quantity = matPrim->quantity;
	limp->length++;
}
