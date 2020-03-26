#include "ui.h"
#include <stdlib.h>

#define MAX_CMD_LEN 100
#define NO_COMMANDS 6
#define PARAMS_L 50

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
void print_mat_prim(MatPrim* matPrim)
{
	printf("Numele produsului: %s\nNumele producatorului: %s\nCantitate: %llu\n\n", matPrim->name, matPrim->provider, matPrim->quantity);
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
		print_mat_prim(limp->matPrim[i]);
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
		if(limp->matPrim[i]->name[0] == criteria[0])
			print_mat_prim(limp->matPrim[i]);
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
		return 1337;
	for (size_t i = 0; i < limp->length; i++)
	{
		if (limp->matPrim[i]->quantity < q)
			print_mat_prim(limp->matPrim[i]);
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
	 - provider
	 - cantitate
	Se ocupa si de validarea numarului de parametrii.
	Returneaza coduri de eroare pentru fiecare caz ce poate sa apara.
	Codurile de eroare pot fi consultate in functia ErrorHandler
*/
int split_params_add(char* params, char** name, char** provider, char** q)
{	
	size_t length = 0;

	char* ptr = strtok(params, " ");
	
	if (ptr == NULL)
		return -2;
	//get the name
	length = strlen(ptr) + 1;
	*name = (char*)malloc(length);
	strcpy(*name, ptr);
	
	//get the producer
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
	{
		free(*name);
		return -2;
	}
	length = strlen(ptr) + 1;
	*provider = (char*)malloc(length);
	strcpy(*provider, ptr);


	//get the quantity
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
	{
		free(*name);
		free(*provider);
		return -2;
	}
	length = strlen(ptr) + 1;
	*q = (char*)malloc(length);
	strcpy(*q, ptr);

	ptr = strtok(NULL, " ");
	if (ptr != NULL)
	{
		free(*name);
		free(*provider);
		free(*q);
		return -2;
	}

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
int split_params_modify(char* params, char** option, char** name, char** modify)
{
	size_t length = 0;

	char* ptr = strtok(params, " ");
	if (ptr == NULL)
		return -2;
	length = strlen(ptr);
	*option = (char*)malloc(length + 1);
	strcpy(*option, ptr);

	ptr = strtok(NULL, " ");
	if (ptr == NULL)
	{
		free(*option);
		return -2;
	}
	length = strlen(ptr);
	*name = (char*)malloc(length + 1);
	strcpy(*name, ptr);

	ptr = strtok(NULL, " ");
	if (ptr == NULL)
	{
		free(*option);
		free(*name);
		return -2;
	}
	length = strlen(ptr);
	*modify = (char*)malloc(length + 1);
	strcpy(*modify, ptr);

	ptr = strtok(NULL, " ");
	if (ptr != NULL)
	{
		free(*option);
		free(*name);
		free(*modify);
		return -2;
	}

	return 0;
}

/*
	Functie specializata in citirea datelor de intrare de la utilizator
	Returneaza numarul e caractere citite
*/
char* read_command(int* cmd_length)
{
	int i = 0;
	int ch;

	char* buffer = (char*)malloc(MAX_CMD_LEN);
	if(buffer != NULL)
		while ((ch = fgetc(stdin)) != EOF)
		{
			if (ch == '\n')
			{
				if(i == 0)
					buffer[i++] = '\n';
				break;
			}
			buffer[i++] = (char)ch;
			if (i == MAX_CMD_LEN - 1)
			{
				char* temp = (char*)malloc(MAX_CMD_LEN * 2);
				for (size_t j = 0; j < strlen(buffer); j++)
				{
					temp[j] = buffer[j];
				}
				free(buffer);
				buffer = temp;
			}
		
		
		}	
	if(buffer != NULL)
		buffer[i] = '\0';
	if (i == 0)
	{
		free(buffer);
		return NULL;
	}
	*cmd_length = i;
	return buffer;
}

/*
	Functie care separa parametrii de comanda dintr-un input de la utilizator
*/
void get_params(char* cmd, char** params, size_t cmd_length, size_t* params_length)
{
	for (size_t i = 0; i < cmd_length; i++)
	{
		if (cmd[i] == ' ')
		{
			*params = (char*)malloc(cmd_length - i + 1);
			char* from_where = cmd + i + 1;
			strncpy(*params, from_where, cmd_length - i);
			*params_length = cmd_length - i;
			cmd[i] = '\0';
			return;

		}
	}
	*params = NULL;
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
int split_params_del(char* params, char** name)
{
	char* ptr = strtok(params, " ");
	if (ptr == NULL)
		return -2;
	size_t length = strlen(ptr);
	*name = (char*)malloc(length + 1);
	strcpy(*name, ptr);

	ptr = strtok(NULL, " ");
	if (ptr != NULL)
	{
		free(*name);
		return -2;
	}

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
int split_params_c_view(char* params, char** option, char** criteria)
{
	char* ptr = strtok(params, " ");
	if (ptr == NULL)
		return -2;
	*option = (char*)malloc(strlen(ptr) + 1);
	strcpy(*option, ptr);

	ptr = strtok(NULL, " ");
	if (ptr == NULL)
	{
		free(*option);
		return -2;
	}
	*criteria = (char*)malloc(strlen(ptr) + 1);
	strcpy(*criteria, ptr);

	ptr = strtok(NULL, " ");
	if (ptr != NULL)
	{
		free(*option);
		free(*criteria);
		return -2;
	}

	return 0;
}

/*
	Functie responsabila pentru functionalitatea: adaugare
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_add(ListMP* limp, char* params)
{
	char* name = NULL;
	char* provider = NULL;
	char* q = NULL;
	int quantity = 0;

	int error_code = 0;

	error_code = split_params_add(params, &name, &provider, &q);
	if (error_code != 0)
		return error_code;

	//validate data type for quantity
	error_code = validate_int(q);
	if (error_code == 0)
		quantity = char2int(q);
	else
	{
		free(name);
		free(provider);
		free(q);
		return error_code;
	}

	error_code = add(limp, name, provider, quantity);
	free(name);
	free(provider);
	free(q);
	return error_code;

}

/*
	Functie responsabila pentru functionalitatea: modifica
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_modify(ListMP* limp, char* params)
{
	char* name = NULL;
	char* option = NULL;
	char* to_modify = NULL;

	int error_code = 0;
	error_code = split_params_modify(params, &option, &name, &to_modify);
	if (error_code != 0)
		return error_code;

	int op = identify_option(option);
	if (op == -1)
	{
		free(name);
		free(option);
		free(to_modify);
		return -3;
	}

	if (op == 2)
		if (validate_int(to_modify) != 0)
		{
			free(name);
			free(option);
			free(to_modify);
			return -1;
		}

	error_code = modify(limp, name, to_modify, op);
	free(name);
	free(option);
	free(to_modify);
	return error_code;
}
/*
	Functie responsabila pentru functionalitatea: stergere
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_del(ListMP* limp, char* params)
{
	char* name = NULL;

	int error_code = 0;
	error_code = split_params_del(params, &name);
	if (error_code != 0)
	{
		free(name);
		return error_code;
	}

	error_code = del(limp, name);
	free(name);
	return error_code;
}
/*
	Functie responsabila pentru functionalitatea: vizualizare dupa criteriu
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_c_view(ListMP* limp, char* params)
{
	char* criteria;
	char* option;
	int error_code = 0;
	int op = 0;

	error_code = split_params_c_view(params, &option, &criteria);
	if (error_code != 0)
		return -2;

	op = identify_option(option);
	if (op == -1 || op == 1)
	{
		free(criteria);
		free(option);
		return -3;
	}

	error_code = c_print(limp, criteria, op);
	if (error_code == 1337)
	{
		free(criteria);
		free(option);
		printf("The list is empty!");
		return 1337;
	}
	free(criteria);
	free(option);
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
	if (params == NULL)
		return -2;

	int error_code = 0;
	
	//get option parameter
	char* ptr = strtok(params, " ");
	if (ptr == NULL)
		return -2;
	size_t length = strlen(ptr);
	char* option = (char*)malloc(length + 1);
	if(option != NULL)
		strcpy(option, ptr);

	//get reversed parameter
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
	{
		free(option);
		return -2;
	}
	length = strlen(ptr);
	char* reversed = (char*)malloc(length + 1);
	if (reversed != NULL)
		strcpy(reversed, ptr);

	ptr = strtok(NULL, " ");
	if (ptr != NULL)
	{
		free(option);
		free(reversed);
		return -2;
	}

	int rev = 0;
	if (reversed != NULL)
	{
		if (strcmp(reversed, "-i") == 0)
			rev = 0;
		else if (strcmp(reversed, "-d") == 0)
			rev = 1;
		else {
			free(option);
			free(reversed);
			return -3;
		}
	}

	int mode = 0;
	if(option != NULL)
		if (strcmp(option, "-n") == 0)
			mode = 0;
		else if (strcmp(option, "-q") == 0)
			mode = 2;
		else
		{
			free(option);
			free(reversed);
			return -3;
		}
	if (mode == 0)
		error_code = sort(limp, rev, NameComparison);
	else
		error_code = sort(limp, rev, QuantityComparison);

	if (error_code == -1)
		printf("The list is empty!\n");
	else
		print_all(limp);

	free(option);
	free(reversed);
	return 1337;
}
/*
	Functie responsabila pentru functionalitatea: tiparire lista
	Returneaza coduri de eroare pentru fiecare eroare
	care vor fi interpretate in functia run() de catre ErrorHandler
*/
int ui_print(ListMP* limp, char* params)
{
	if (params != NULL)
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
	int cmd_length = 0, command_index = 0;

	//COMMANDS 
	char* menu = "\n  add - Adds <materie_prima>\t  ex: add faina panemar 12\n\n  modify - Modifies <materie_prima>\t  ex: modify -n faina paine\n\t-n -> the name,\n\t-p -> the producer,\n\t-q -> the quantity\n\n  del - Deletes <materie_prima>\t  ex: del paine\n\n  c_view - View the list based on a criteria \t  ex: c_view -n p\n\t-n -> <materiile_prime> which names start with a character,\n\t-q -> <materiile_prime> which quantity is less than a given number;\n\n  o_view - View the list ordered by:\t  ex: o_view -q\n  Primul parametru:\n\t-n -> name\n\t-q -> quantity\n  Al doilea parametru:\n\t-i increasing order\n\t-d decreasing order\n\n  print - Prints the list of <materii_prime>\tex: print\n\n  exit - Exits the program\n\n";

	//Indexul comenzii gasite aici corespunde indexului functiei care trebuie preluata din lista cu pointeri "commander"
	char* commands[MAX_CMD_LEN] = { "add", "modify", "del", "c_view", "o_view", "print" };

	//Lista cu pointeri catre functiile care trebuiesc apelate in functie de comanda primita
	int(*commander[NO_COMMANDS])(ListMP* limp, char* params) = { ui_add, ui_modify, ui_del, ui_c_view, ui_o_view, ui_print };

	//PARAMS
	char* params = NULL;
	size_t params_length = 0;

	printf("Type \"help\" for the menu\n");

	while (true)
	{
		_write(1, ">>", 2);
		cmd_length = -1;
		char* cmd = read_command(&cmd_length);
		if (cmd[0] == '\n')
		{
			free(cmd);
			continue;
		}
		if (cmd_length > MAX_CMD_LEN)
		{
			printf("Parameters are too large!\n");
			free(cmd);
			continue;
		}

		if (cmd_length != -1)
		{
			//separa parametrii de comanda din string-ul primit de la utilizator
			get_params(cmd, &params, cmd_length, &params_length);

			if (strcmp(cmd, "help") == 0) {
				printf("%s", menu);
				free(cmd);
				continue;
			}

			if (strcmp(cmd, "exit") == 0)
			{
				printf("Process terminated!\n");
				free(cmd);
				break;
			}

			//valideaza comanda si intoarce indexul din lista de pointeri catre functii
			command_index = validate_command(cmd, commands);

			if (command_index != -1)
			{		
				int error_code = 0;
				error_code = commander[command_index](limp, params);
				if (error_code != 0)
					printf("%s\n", ErrorHandler(error_code));
				else
					printf("Successful!\n");
				if(cmd_length != 0)
					free(cmd);
				if(params_length != 0)
					free(params);
			}	

			else {
				free(cmd);
				printf("Unknown command!\nType \"help\" to see the commands!\n");
			}
		}
		else
		{
			printf("Unknown command!\nType \"help\" to see the commands!\n");

			free(cmd);
		}
		
	}
}