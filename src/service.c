#include "service.h"

int validate_unique(const ListMP* limp, char* name)
{
	for (size_t i = 0; i < limp->length; i++)
	{
		if (strcmp(limp->matPrim[i].name, name) == 0)
			return 1;
	}
	return 0;
}

size_t search(ListMP* limp, char* name)
{
	for (size_t i = 0; i < limp->length; i++)
	{
		if (strcmp(limp->matPrim[i].name, name) == 0)
			return i;
	}
	return -1;
}

int add(ListMP* limp, char* name, char* producator, int quantity)
{	
	//Data validation
	int errors = 0;
	errors += validate_string(name);
	errors += 2 * validate_string(producator);
	errors += 4 * validate_quantity(quantity);
	if (errors != 0)
		return errors;

	if (validate_unique == 0)
	{
		m_prim matPrim = create(name, producator, quantity);
		l_add(limp, &matPrim);
	}
	else
	{
		size_t index = search(limp, name);
		limp->matPrim[index].quantity += quantity;
	}
	return 0;

}

void print_mat_prim(m_prim* matPrim)
{
	printf("Numele produsului: %s\nNumele producatorului: %s\nCantitate: %d\n\n", matPrim->name, matPrim->producator, matPrim->quantity);
}

void print_all(ListMP* limp)
{
	for (size_t i = 0; i < limp->length; i++)
	{
		print_mat_prim(&(limp->matPrim[i]));
	}
}