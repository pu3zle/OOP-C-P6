#include "model.h"
#pragma warning(disable:4996)

MatPrim MatPrimCreate(char* name, char* provider, size_t quantity)
{
	MatPrim matPrim;

	size_t nL = strlen(name);
	matPrim.name_length = nL;
	matPrim.name = (char*)malloc(nL + 1);
	if(matPrim.name != NULL)
		strncpy(matPrim.name, name, nL);
	matPrim.name[nL] = '\0';

	size_t pL = strlen(provider);
	matPrim.provider_length = pL;
	matPrim.provider = (char*)malloc(pL + 1);
	if(matPrim.provider != NULL)
		strncpy(matPrim.provider, provider, pL);
	matPrim.provider[pL] = '\0';


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

void set_provider(MatPrim* matPrim, char* provider)
{
	size_t n = strlen(provider);
	//free(matPrim->producator);
	char* temp = matPrim->provider;
	matPrim->provider = (char*)malloc(n + 1);
	if(matPrim->provider != NULL)
		strcpy(matPrim->provider, provider);
	
	free(temp);

	if(matPrim->provider != NULL)
		matPrim->provider[n] = '\0';
	matPrim->provider_length = n;
}

void set_quantity(MatPrim* matPrim, int q)
{
	matPrim->quantity = q;
}

ListMP l_create()
{
	ListMP limp;
	limp.size = 3;
	limp.length = 0;
	limp.matPrim = (MatPrim*)malloc(limp.size * sizeof(MatPrim));
	return limp;
}

void destroyM_Prim(MatPrim* matPrim)
{
	free(matPrim->name);
	free(matPrim->provider);
}

void destroyListMP(ListMP* limp)
{
	for (size_t i = 0; i < limp->length; i++)
	{
		free(limp->matPrim[i].name);
		free(limp->matPrim[i].provider);
	}
	free(limp->matPrim);
}

void CpyLimp(MatPrim* m1, MatPrim* m2)
{
	m1->name = m2->name;
	m1->provider = m2->provider;
	m1->name_length = m2->name_length;
	m1->provider_length = m2->provider_length;
	m1->quantity = m2->quantity;
}

void ReserveNewMatPrim(MatPrim** mat_prim, size_t NewSize, size_t Length)
{
	MatPrim* temp = (MatPrim*)malloc(NewSize * sizeof(MatPrim));

	for (size_t i = 0; i < Length; i++)
	{
		CpyLimp(&(temp[i]), &((*mat_prim)[i]));
	}

	free(*mat_prim);
	*mat_prim = temp;
}
