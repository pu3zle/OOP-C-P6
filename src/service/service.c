#include "service.h"
#pragma warning(disable:4996)

void l_add(ListMP* limp, m_prim* matPrim)
{
	strcpy(limp->matPrim[limp->length].name, matPrim->name);
	strcpy(limp->matPrim[limp->length].producator, matPrim->producator);
	limp->matPrim[limp->length].quantity = matPrim->quantity;
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
	{
		if (strcmp(limp->matPrim[i].name, name) == 0)
			return 1;
	}
	return 0;
}

 int search(ListMP* limp, char* name)
{
	for (int i = 0; i < limp->length; i++)
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

	if (validate_unique(limp, name) == 0)
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
			set_prod(&(limp->matPrim[found]), modify);
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

void cpy(m_prim* m1, m_prim* m2)
{
	strcpy(m1->name, m2->name);
	strcpy(m1->producator, m2->producator);
	m1->name_length = m2->name_length;
	m1->prod_length = m2->prod_length;
	m1->quantity = m2->quantity;
}

int del(ListMP* limp, char* name)
{
	int position = search(limp, name);
	if (position == -1)
		return -4;

	if (position == limp->length - 1)
		limp->length--;

	else {

		for (size_t i = position; i < limp->length - 1; i++)
			cpy(&(limp->matPrim[i]), &(limp->matPrim[i + 1]));
		limp->length--;
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
				m_prim aux;
				cpy(&aux, &(limp->matPrim[i]));
				cpy(&(limp->matPrim[i]), &(limp->matPrim[j]));
				cpy(&(limp->matPrim[j]), &aux);
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
				m_prim aux;
				cpy(&aux, &(limp->matPrim[i]));
				cpy(&(limp->matPrim[i]), &(limp->matPrim[j]));
				cpy(&(limp->matPrim[j]), &aux);
			}
		}
	}
	return 0;
}
