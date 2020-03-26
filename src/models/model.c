#include "model.h"

MatPrim* MatPrimCreate(char* name, char* provider, size_t quantity)
{
	MatPrim* matPrim = (MatPrim*)malloc(sizeof(MatPrim));
	size_t nL = strlen(name);
	if (matPrim != NULL)
	{
		matPrim->name_length = nL;
		matPrim->name = (char*)malloc(nL + 1);
		if (matPrim->name != NULL)
		{
			strncpy(matPrim->name, name, nL);
			matPrim->name[nL] = '\0';
		}
		size_t pL = strlen(provider);
		matPrim->provider_length = pL;
		matPrim->provider = (char*)malloc(pL + 1);
		if (matPrim->provider != NULL)
		{

			strncpy(matPrim->provider, provider, pL);
			matPrim->provider[pL] = '\0';
		}
		matPrim->quantity = quantity;
	}
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

void destroyM_Prim(MatPrim* matPrim)
{
	free(matPrim->name);
	free(matPrim->provider);
	free(matPrim);
}

void CpyLimp(MatPrim* m1, MatPrim* m2)
{
	m1->name = m2->name;
	m1->provider = m2->provider;
	m1->name_length = m2->name_length;
	m1->provider_length = m2->provider_length;
	m1->quantity = m2->quantity;
}

void ReserveNewMatPrim(MatPrim*** mat_prim, size_t NewSize, size_t Length)
{
	MatPrim** temp = (MatPrim**)malloc(NewSize * sizeof(MatPrim*));
	if(temp != NULL)
	for (size_t i = 0; i < Length; i++)
	{
		temp[i] = (*(mat_prim))[i];
	}

	free(*mat_prim);
	*mat_prim = temp;
}

