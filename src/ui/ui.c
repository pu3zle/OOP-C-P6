#include "ui.h"
#pragma warning(disable:4996)

#define MAX_CMD_LEN 50
#define NO_COMMANDS 6
#define PARAMS_L 20

/*
	Functie care verifica daca un sir de caractere poate fi interpretat ca un numar
	Params: un string
	Returns: true / false 
*/
int validate_int(char* q)
{	
	size_t n = strlen(q);
	if (q[0] < '0' || q[0] > '9')
		if (q[0] != '-')
			return -1;
	for (size_t i = 1; i < n; i++)
	{
		if (q[i] < '0' || q[i] > '9')
			return -1;
	}
	return 0;
}

/*
	Functie care afiseaza elementele unei materii prime intr-un format stabilit
	Params: o materie prima
*/
void print_mat_prim(m_prim* matPrim)
{
	printf("Numele produsului: %s\nNumele producatorului: %s\nCantitate: %llu\n\n", matPrim->name, matPrim->producator, matPrim->quantity);
}

/*
	Functie care tipareste toate elementele din lista de materii prime
	Params: lista de materii prime
	Returneaza -1 daca lista este goala, 0 altfel
*/
int print_all(ListMP* limp)
{
	if (limp->length == 0)
		return -1;
	for (size_t i = 0; i < limp->length; i++)
	{
		print_mat_prim(&(limp->matPrim[i]));
	}
	return 0;
}

/*
	Functie care tipareste toate materiile prime dintr-o lista care incep cu o litera data
	Params: limp - lista de materii prime, criteria - litera cu care sa inceapa
	Returns: -1 daca lista e goala, 0 altfel
*/
int print_all_c_letter(ListMP* limp, char* criteria)
{
	if (limp->length == 0)
		return -1;
	for (size_t i = 0; i < limp->length; i++)
	{
		if(limp->matPrim[i].name[0] == criteria[0])
			print_mat_prim(&(limp->matPrim[i]));
	}
	return 0;
}

/*
	Functie care tipareste toate materiile prime dintr-o lista cu cantitatea mai mica decat o cantitate data
	Params: limp - lista de materii prime, q - cantitatea data
	Returns: -1 daca lista e goala, 0 altfel
*/
int print_all_q_lower(ListMP* limp, size_t q)
{
	if (limp->length == 0)
		return -1;
	for (size_t i = 0; i < limp->length; i++)
	{
		if (limp->matPrim[i].quantity < q)
			print_mat_prim(&(limp->matPrim[i]));
	}
	return 0;
}

/*
	Functie ajutatoare pentru functionalitatea 4). Se ocupa de alegerea dintre cele 2 moduri ale functionalitatii:
		- modul " -n ", tiparire materii prime care contin o litera data
		- modul " -q ", tiparire materii prime cu cantitate mai mica decat o cantitate data
	Functia se mai ocupa si de validarea datelor dpdv logic.
	Returneaza coduri de eroare pentru fiecare caz ce poate sa apara.
	Codurile de eroare pot fi consultate in functia ErrorHandler
*/
int c_print(ListMP* limp, char* criteria, int mode)
{
	int error_code = 0;
	if (mode == 0)
	{
		error_code = validate_string(criteria);
		if (error_code != 0)
			return 1;
		if (strlen(criteria) > 1)
			return -5;
		error_code = print_all_c_letter(limp, criteria);

	}
	else 
	{
		error_code = validate_int(criteria);
		if (error_code != 0)
			return -1;
		int value = char2int(criteria);
		if (validate_quantity(value) != 0)
			return 4;
		error_code = print_all_q_lower(limp, (size_t)value);

	}
	return error_code;
}

/*
	Functie care sparge string-ul "params" in elementele componente necesare operatiei de adaugare:
	 - name
	 - producator
	 - cantitate
	Se ocupa si de validarea numarului de parametrii.
	Returneaza coduri de eroare pentru fiecare caz ce poate sa apara.
	Codurile de eroare pot fi consultate in functia ErrorHandler
*/
int split_params_add(char* params, char* name, char* prod, char* q)
{	
	char* ptr = strtok(params, " ");
	
	if (ptr == NULL)
		return -2;
	//get the name
	strcpy(name, ptr);
	
	//get the producer
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return -2;
	strcpy(prod, ptr);


	//get the quantity
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return -2;
	strcpy(q, ptr);

	ptr = strtok(NULL, " ");
	if (ptr != NULL)
		return -2;

	return 0;
}

/*
	Functie care sparge string-ul "params" in elementele componente necesare operatiei de modificare:
	 - optiune
	 - nume
	 - element cu care va fi inlocuit elementul ce trebuie modificat
	Se ocupa si de validarea numarului de parametrii.
	Returneaza coduri de eroare pentru fiecare caz ce poate sa apara.
	Codurile de eroare pot fi consultate in functia ErrorHandler
*/
int split_params_modify(char* params, char* option, char* name, char* modify)
{
	char* ptr = strtok(params, " ");
	if (ptr == NULL)
		return -2;

	strcpy(option, ptr);

	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return -2;
	strcpy(name, ptr);

	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return -2;
	strcpy(modify, ptr);

	ptr = strtok(NULL, " ");
	if (ptr != NULL)
		return -2;

	return 0;
}

/*
	Functie specializata in citirea datelor de intrare de la utilizator
	Returneaza numarul e caractere citite
*/
size_t read_command(char* buffer)
{
	size_t i = 0;
	size_t stream_length = 0;
	int ch;

	while ((ch = fgetc(stdin)) != EOF)
	{
		stream_length++;
		if (i + 1 < MAX_CMD_LEN)
		{
			if (ch == '\n')
			{
				if(i == 0)
					buffer[i++] = ch;
				break;
			}
			buffer[i++] = ch;
		}
		
	}
	buffer[i] = '\0';
	if (i == 0)
		return -1;
	if (stream_length > MAX_CMD_LEN)
		return -1;
	return i;
}

/*
	Functie care separa parametrii de comanda dintr-un input de la utilizator
*/
void get_params(char* cmd, char* params, size_t cmd_length, size_t* params_length)
{
	for (size_t i = 0; i < cmd_length; i++)
	{
		if (cmd[i] == ' ')
		{
			char* from_where = cmd + i + 1;
			strncpy(params, from_where, PARAMS_L);
			*params_length = cmd_length - i;
			cmd[i] = '\0';
			return;

		}
	}
	strcpy(params, "");
	*params_length = 0;
}

/*
	Functie care se ocupa cu returnarea unui cod de eroare pentru fiecare eroare
*/
const char* ErrorHandler(int error_code)
{
	if (error_code == -5)
		return "The argument needs to be a single character!";
	else if (error_code == -4)
		return "Product not found!";
	else if (error_code == -3)
		return "Incorrect option!";
	else if (error_code == -2)
		return "Incorrect number of parameters!";
	else if (error_code == -1)
		return "Last argument must be an integer (quantity)";
	else if (error_code == 1)
		return "Name must not be equal to NULL";
	else if (error_code == 2)
		return "Manufacturer name must not be equal to NULL";
	else if (error_code == 3)
		return "Name & manufacturer must not be empty strings";
	else if (error_code == 4)
		return "Quantity must be a positive number";
	else if (error_code == 5)
		return "Quantity must be a positive number\nName must not be equal to NULL";
	else if (error_code == 6)
		return "Quantity must be a positive number\nManufacturer name must not be equal to NULL";
	else if (error_code == 7)
		return "Quantity must be a positive number\nName & manufacturer must not be empty strings";
	else if (error_code == 1337)
		return "";
	else return "Unknown error!\n";
}

/*
	Functie folosita pentru identificarea comenzilor
	Returns: indexul comenzii
*/
int validate_command(char* buffer, char* commands[MAX_CMD_LEN])
{
	for (int i = 0; i < NO_COMMANDS; i++)
	{
		if (strcmp(buffer, commands[i]) == 0)
			return i;
	}
	return -1;
}
/*	
	Functie folosita pentru functionalitatile care au optiuni.
	Identifica optiunea si returneaza un cod pentru fiecare optiune.
	Daca nu gaseste o optiune, returneaza -1
*/
int identify_option(char* option)
{
	if (strcmp("-n", option) == 0)
		return 0;
	if (strcmp("-p", option) == 0)
		return 1;
	if (strcmp("-q", option) == 0)
		return 2;

	return -1;
}

/*
	Functie care sparge string-ul "params" in elementele componente necesare operatiei de delete:
	 - nume
	Se ocupa si de validarea numarului de parametrii.
	Returneaza coduri de eroare pentru fiecare caz ce poate sa apara.
	Codurile de eroare pot fi consultate in functia ErrorHandler
*/
int split_params_del(char* params, char* name)
{
	char* ptr = strtok(params, " ");
	if (ptr == NULL)
		return -2;

	strcpy(name, ptr);

	ptr = strtok(NULL, " ");
	if (ptr != NULL)
		return -2;

	return 0;
}
/*
	Functie care sparge string-ul "params" in elementele componente necesare operatiei de vizualizare lista dupa criteriu:
	 - optiune
	 - criteriu
	Se ocupa si de validarea numarului de parametrii.
	Returneaza coduri de eroare pentru fiecare caz ce poate sa apara.
	Codurile de eroare pot fi consultate in functia ErrorHandler
*/
int split_params_c_view(char* params, char* option, char* criteria)
{
	char* ptr = strtok(params, " ");
	if (ptr == NULL)
		return -2;
	strcpy(option, ptr);

	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return -2;
	strcpy(criteria, ptr);

	ptr = strtok(NULL, " ");
	if (ptr != NULL)
		return -2;

	return 0;
}

/*
	Functie responsabila pentru functionalitatea: adaugare
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_add(ListMP* limp, char* params)
{
	char name[PARAMS_L];
	char prod[PARAMS_L];
	char q[PARAMS_L];
	int quantity = 0;

	int error_code = 0;

	error_code = split_params_add(params, name, prod, q);
	if (error_code != 0)
		return error_code;

	//validate data type for quantity
	error_code = validate_int(q);
	if (error_code == 0)
		quantity = char2int(q);
	else return error_code;

	error_code = add(limp, name, prod, quantity);
	return error_code;

}

/*
	Functie responsabila pentru functionalitatea: modifica
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_modify(ListMP* limp, char* params)
{
	char name[PARAMS_L];
	char option[PARAMS_L];
	char to_modify[PARAMS_L];

	int error_code = 0;
	error_code = split_params_modify(params, option, name, to_modify);
	if (error_code != 0)
		return error_code;

	int op = identify_option(option);
	if (op == -1)
		return -3;

	if (op == 2)
		if (validate_int(to_modify) != 0)
			return -1;

	error_code = modify(limp, name, to_modify, op);

	return error_code;
}
/*
	Functie responsabila pentru functionalitatea: stergere
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_del(ListMP* limp, char* params)
{
	char name[PARAMS_L];

	int error_code = 0;
	error_code = split_params_del(params, name);
	if (error_code != 0)
		return error_code;

	error_code = del(limp, name);
	return error_code;
}
/*
	Functie responsabila pentru functionalitatea: vizualizare dupa criteriu
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_c_view(ListMP* limp, char* params)
{
	char criteria[PARAMS_L];
	char option[PARAMS_L];
	int error_code = 0;
	int op = 0;

	error_code = split_params_c_view(params, option, criteria);
	if (error_code != 0)
		return -2;

	op = identify_option(option);
	if (op == -1 || op== 1)
		return -3;

	error_code = c_print(limp, criteria, op);
	if (error_code == -1)
	{
		printf("The list is empty!");
		return 1337;
	}
	if (error_code == 0)return 1337;
	return error_code;
}
/*
	Functie responsabila pentru functionalitatea: vizualizare cu sortare
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_o_view(ListMP* limp, char* params)
{
	int error_code = 0;
	char option[PARAMS_L];
	char* ptr = strtok(params, " ");
	if (ptr == NULL)
		return -2;
	strcpy(option, ptr);

	ptr = strtok(NULL, " ");
	if (ptr != NULL)
		return -2;

	int mode = 0;
	if (strcmp(option, "-n") == 0)
		mode = 0;
	else if (strcmp(option, "-q") == 0)
		mode = 2;
	else return -3;

	if (mode == 0)
		error_code = sort_name(limp);
	else
		error_code = sort_quantity(limp);

	if (error_code == -1)
		printf("The list is empty!\n");
	else
		print_all(limp);
	return 1337;
}
/*
	Functie responsabila pentru functionalitatea: tiparire lista
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_print(ListMP* limp, char* params)
{
	char* ptr = strtok(params, " ");
	if (ptr != NULL)
		return -2;
	int code = print_all(limp);
	if (code == -1)
		printf("The list is empty!\n");
	return 1337;
}

/*
	Functia care se ocupa de interpretarea datelor introduse de utilizator si actionare
	in conformitate cu acestea
*/
void run(ListMP* limp)
{
	char cmd[MAX_CMD_LEN];
	size_t cmd_length = 0, command_index = 0;

	//COMMANDS 
	char* menu = "\n  add - Adds <materie_prima>\t  ex: add faina panemar 12\n\n  modify - Modifies <materie_prima>\t  ex: modify -n faina paine\n\t-n -> the name,\n\t-p -> the producer,\n\t-q -> the quantity\n\n  del - Deletes <materie_prima>\t  ex: del paine\n\n  c_view - View the list based on a criteria \t  ex: c_view -n p\n\t-n -> <materiile_prime> which names that start with a character,\n\t-q -> <materiile_prime> which quantity is less than a given number;\n\n  o_view - View the list ordered by:\t  ex: o_view -q\n\t-n -> name\n\t-q -> quantity\n\n  print - Prints the list of <materii_prime>\tex: print\n\n  exit - Exits the program\n\n";

	char* commands[MAX_CMD_LEN] = { "add", "modify", "del", "c_view", "o_view", "print" };

	int(*commander[NO_COMMANDS])(ListMP* limp, char* params) = { ui_add, ui_modify, ui_del, ui_c_view, ui_o_view, ui_print };

	//PARAMS
	char params[PARAMS_L];
	size_t params_length = 0;

	printf("Type \"help\" for the menu\n");

	while (true)
	{
		_write(1, ">>", 2);
		cmd_length = read_command(cmd);
		
		if (cmd[0] == '\n')continue;

		if (cmd_length != -1)
		{
			get_params(cmd, params, cmd_length, &params_length);

			if (strcmp(cmd, "help") == 0) {
				printf("%s", menu);
				continue;
			}

			if (strcmp(cmd, "exit") == 0)
			{
				printf("Process terminated!\n");
				break;
			}

			command_index = validate_command(cmd, commands);

			if (command_index != -1)
			{		
				int error_code = 0;
				error_code = commander[command_index](limp, params);
				if (error_code != 0)
					printf("%s\n", ErrorHandler(error_code));
				else
					printf("Successful!\n");
			}	

			else {
				printf("Unknown command!\nType \"help\" to see the commands!\n");
			}
		}
		else
			printf("Unknown command!\nType \"help\" to see the commands!\n");
	}
		
}