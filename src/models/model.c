#include "model.h"
#pragma warning(disable:4996)

MatPrim MatPrimCreate(char* name, char* producator, size_t quantity)
{
	MatPrim matPrim;

	size_t nL = strlen(name);
	matPrim.name_length = nL;
	matPrim.name = (char*)malloc(nL + 1);
	if(matPrim.name != NULL)
		strncpy(matPrim.name, name, nL);
	matPrim.name[nL] = '\0';

	size_t pL = strlen(producator);
	matPrim.prod_length = pL;
	matPrim.producator = (char*)malloc(pL + 1);
	if(matPrim.producator != NULL)
		strncpy(matPrim.producator, producator, pL);
	matPrim.producator[pL] = '\0';

	matPrim.quantity = quantity;
	return matPrim;
}

void set_name(MatPrim* matPrim, char* name)
{
	size_t n = strlen(name);
	free(matPrim->name);

	matPrim->name = (char*)malloc(n + 1);
	strcpy(matPrim->name, name);

	if(matPrim->name != NULL)
		matPrim->name[n] = '\0';
	matPrim->name_length = n;
}

void set_prod(MatPrim* matPrim, char* prod)
{
	size_t n = strlen(prod);
	//free(matPrim->producator);
	char* temp = matPrim->producator;
	matPrim->producator = (char*)malloc(n + 1);
	if(matPrim->producator != NULL)
		strcpy(matPrim->producator, prod);
	
	free(temp);

	if(matPrim->producator != NULL)
		matPrim->producator[n] = '\0';
	matPrim->prod_length = n;
}

void set_quantity(MatPrim* matPrim, int q)
{
	matPrim->quantity = q;
}

ListMP l_create()
{
	ListMP limp;
	limp.length = 0;
	return limp;
}

void destroyM_Prim(MatPrim* matPrim)
{
	free(matPrim->name);
	free(matPrim->producator);
}

void destroyListMP(ListMP* limp)
{
	for (size_t i = 0; i < limp->length; i++)
	{
		free(limp->matPrim[i].name);
		free(limp->matPrim[i].producator);
	}
}

void CpyLimp(MatPrim* m1, MatPrim* m2)
{
	m1->name = m2->name;
	m1->producator = m2->producator;
	m1->name_length = m2->name_length;
	m1->prod_length = m2->prod_length;
	m1->quantity = m2->quantity;
}
