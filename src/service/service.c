#include "service.h"


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
		if (strcmp(limp->matPrim[i]->name, name) == 0)
			return 1;

	return 0;
}

 int search(ListMP* limp, char* name)
{
	for (int i = 0; i < limp->length; i++)
		if (strcmp(limp->matPrim[i]->name, name) == 0)
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
		MatPrim* matPrim = MatPrimCreate(name, provider, quantity);
		l_add(limp, matPrim);
	}
	else
	{
		size_t index = search(limp, name);
		limp->matPrim[index]->quantity += quantity;
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
			set_name(limp->matPrim[found], modify);
		else return 1;
		break;
	case 1:
		error_code = validate_string(modify);
		if (error_code == 0)
			set_provider(limp->matPrim[found], modify);
		else return 2;
		break;
	case 2:
		int q = char2int(modify);
		error_code = validate_quantity(q);
		if (error_code == 0)
			set_quantity(limp->matPrim[found], q);
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
	int error_code = l_del(limp, position);
	return error_code;
}

// Functie care schimba valorile a doua materii prime intre ele
void swap(MatPrim* a, MatPrim* b)
{
	MatPrim aux;
	CpyLimp(&aux, a);
	CpyLimp(a, b);
	CpyLimp(b, &aux);
}

// Functie auxiliara pentru sortare
// Compara cantitatile unor materii prime
int QuantityComparison(MatPrim* a, MatPrim* b)
{
	if (a->quantity >= b->quantity)
		return 1;
	else 
		return -1;
}

// Functie auxiliara pentru sortare
// Compara numele unor materii prime
int NameComparison(MatPrim* a, MatPrim* b)
{
	return strcmp(a->name, b->name);
}


/*
	
*/
int sort(ListMP* limp, int reverse, int(*Comparison)(MatPrim*, MatPrim*))
{
	reverse = reverse == 0 ? 1 : -1;
	if (limp->length == 0) 
		return -1;
	for (size_t i = 0; i < limp->length - 1; i++)
	{
		for (size_t j = i + 1; j < limp->length; j++)
		{
			if ((reverse * Comparison(limp->matPrim[i], limp->matPrim[j])) == 1)
				swap(limp->matPrim[i], limp->matPrim[j]);
		}
	}
	return 0;
}

