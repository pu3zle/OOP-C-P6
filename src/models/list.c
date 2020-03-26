#include "list.h"


ListMP l_create()
{
	ListMP limp;
	limp.size = 3;
	limp.length = 0;
	limp.matPrim = (MatPrim**)malloc(limp.size * sizeof(MatPrim*));
	return limp;
}

void destroyListMP(ListMP* limp)
{
	for (size_t i = 0; i < limp->length; i++)
	{
		destroyM_Prim(limp->matPrim[i]);
	}
	free(limp->matPrim);
}

void l_add(ListMP* limp, MatPrim* matPrim)
{
	if (limp->length == limp->size)
	{
		ReserveNewMatPrim(&(limp->matPrim), 2 * limp->size, limp->length);
		limp->size *= 2;
	}
	//limp->matPrim[limp->length] = (MatPrim*)malloc(sizeof(MatPrim));
	limp->matPrim[limp->length] = matPrim;
	//CpyLimp(limp->matPrim[limp->length], matPrim);
	limp->length++;
}

int l_del(ListMP* limp, int position)
{
	if (position == -1)
		return -4;

	if (position == limp->length - 1)
	{
		limp->length--;
		destroyM_Prim(limp->matPrim[position]);
	}

	else {
		destroyM_Prim(limp->matPrim[position]);
		limp->matPrim[position] = (MatPrim*)malloc(sizeof(MatPrim));
		for (size_t i = position; i < limp->length - 1; i++)
			CpyLimp(limp->matPrim[i], limp->matPrim[i + 1]);

		limp->length--;

		//Din moment ce am tras sirul la stanga, doar am mutat pointerii de la un element la altul,
		//nu am facut strcpy. In cazul asta, ultimul element si penultimul element pointeaza catre acelasi element.
		//Pun null la ultimul ca sa nu se stearga ambele cand dau free
		limp->matPrim[limp->length]->name = NULL;
		limp->matPrim[limp->length]->provider = NULL;
		destroyM_Prim(limp->matPrim[limp->length]);
	}
	return 0;
}