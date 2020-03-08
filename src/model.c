#include "model.h"

m_prim create(char* name, char* producator)
{
	m_prim matPrim;
	size_t nL = strlen(name);
	matPrim.name_length = nL;
	strcpy(matPrim.name, name, nL);

	size_t pL = strlen(producator);
	matPrim.prod_length = pL;
	strcpy(matPrim.producator, producator, pL);
	return matPrim;
}
