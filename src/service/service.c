#include "service.h"
#pragma warning(disable:4996)

void l_add(ListMP* limp, MatPrim* matPrim)
{
	CpyLimp(&(limp->matPrim[limp->length]), matPrim);
	limp->length++;
}

int char2int(char* q)
{
	int x = 0;
	size_t n = strlen(q);
	for (size_t i = 0; i < n; i++)
	{
		x = x * 10 + q[i] - '0';
	}
	return x;
}

int validate_unique(const ListMP* limp, char* name)
{
	for (size_t i = 0; i < limp->length; i++)
		if (strcmp(limp->matPrim[i].name, name) == 0)
			return 1;

	return 0;
}

 int search(ListMP* limp, char* name)
{
	for (int i = 0; i < limp->length; i++)
		if (strcmp(limp->matPrim[i].name, name) == 0)
			return i;
	return -1;
}

int add(ListMP* limp, char* name, char* provider, int quantity)
{	
	//Data validation
	int errors = 0;
	errors += validate_string(name);
	errors += 2 * validate_string(provider);
	errors += 4 * validate_quantity(quantity);
	if (errors != 0)
		return errors;

	if (validate_unique(limp, name) == 0)
	{
		MatPrim matPrim = MatPrimCreate(name, provider, quantity);
		if (limp->length == limp->size)
		{
			ReserveNewMatPrim(&(limp->matPrim), 2 * limp->size, limp->length);
			limp->size *= 2;
		}
		l_add(limp, &matPrim);
	}
	else
	{
		size_t index = search(limp, name);
		limp->matPrim[index].quantity += quantity;
	}
	return 0;

}

int modify(ListMP* limp, char* name, char* modify, int op)
{
	int found = search(limp, name);
	if (found == -1)
		return -4;

	int error_code = 0;

	switch (op)
	{
	case 0:
		error_code = validate_string(modify);
		if (error_code == 0)
			set_name(&(limp->matPrim[found]), modify);
		else return 1;
		break;
	case 1:
		error_code = validate_string(modify);
		if (error_code == 0)
			set_provider(&(limp->matPrim[found]), modify);
		else return 2;
		break;
	case 2:
		int q = char2int(modify);
		error_code = validate_quantity(q);
		if (error_code == 0)
			set_quantity(&(limp->matPrim[found]), q);
		else return 4;
		break;
	default:
		break;
	}
	return 0;

}


int del(ListMP* limp, char* name)
{
	int position = search(limp, name);
	if (position == -1)
		return -4;

	if (position == limp->length - 1)
	{
		limp->length--;
		free(limp->matPrim[position].name);
		free(limp->matPrim[position].provider);
	}

	else {
		free(limp->matPrim[position].name);
		free(limp->matPrim[position].provider);

		for (size_t i = position; i < limp->length - 1; i++)
			CpyLimp(&(limp->matPrim[i]), &(limp->matPrim[i + 1]));

		limp->length--;

		limp->matPrim[limp->length].name = NULL;
		limp->matPrim[limp->length].provider = NULL;
		free(limp->matPrim[limp->length].name);
		free(limp->matPrim[limp->length].provider);

	}

	if (limp->length == limp->size / 4)
	{
		ReserveNewMatPrim(&(limp->matPrim), limp->size / 2, limp->length);
		limp->size /= 2;
	}

	return 0;
}

int sort_name(ListMP* limp)
{
	if (limp->length == 0) return -1;
	for (size_t i = 0; i < limp->length - 1; i++)
	{
		for (size_t j = i+1; j < limp->length; j++)
		{
			if (strcmp(limp->matPrim[i].name, limp->matPrim[j].name) == 1)
			{
				MatPrim aux;
				CpyLimp(&aux, &(limp->matPrim[i]));
				CpyLimp(&(limp->matPrim[i]), &(limp->matPrim[j]));
				CpyLimp(&(limp->matPrim[j]), &aux);
			}
		}
	}
	return 0;
}

int sort_quantity(ListMP* limp)
{
	if (limp->length == 0) return -1;
	for (size_t i = 0; i < limp->length - 1; i++)
	{
		for (size_t j = i + 1; j < limp->length; j++)
		{
			if (limp->matPrim[i].quantity > limp->matPrim[j].quantity)
			{
				MatPrim aux;
				CpyLimp(&aux, &(limp->matPrim[i]));
				CpyLimp(&(limp->matPrim[i]), &(limp->matPrim[j]));
				CpyLimp(&(limp->matPrim[j]), &aux);
			}
		}
	}
	return 0;
}
