#include "service.h"


int add(ListMP* limp, char* name, char* producator, int quantity)
{	
	//Data validation
	int errors = 0;
	errors += validate_string(name);
	errors += 2 * validate_string(producator);
	errors += 4 * validate_quantity(quantity);
	if (errors != 0)
		return errors;

	m_prim matPrim = create(name, producator, quantity);

}