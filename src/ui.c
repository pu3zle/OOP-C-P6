
#include "ui.h"


#define MAX_CMD_LEN 30
#define NO_COMMANDS 5
#define PARAMS_L 20

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

int split_params(char* params, char* name, char* prod, char* q)
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

const char* ErrorHandler(int error_code)
{
	if (error_code == -2)
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
	else return "Unknown error!\n";
}

int validate_command(char* buffer, char* commands[MAX_CMD_LEN])
{
	for (int i = 0; i < NO_COMMANDS; i++)
	{
		if (strcmp(buffer, commands[i]) == 0)
			return i;
	}
	return -1;
}

//IMPLEMENT THE FUNCTIONS
int ui_add(ListMP* limp, char* params)
{	
	char name[20];
	char prod[20];
	char q[20];
	int quantity = 0;

	int error_code = 0;

	error_code = split_params(params, name, prod, q);
	if (error_code != 0)
		return error_code;

	//validate data type for quantity
	error_code = validate_int(q);
	if(error_code == 0)
		quantity = char2int(q);
	else return error_code;

	error_code = add(limp, name, prod, quantity);
	return error_code;
	//printf("%s\n%s\n%d\n", name, prod, quantity);

}
int ui_modify(ListMP* limp, char* params)
{
	return 0;
}
int ui_del(ListMP* limp, char* params)
{
	return 0;
}
int ui_c_view(ListMP* limp, char* params)
{
	return 0;
}
int ui_o_view(ListMP* limp, char* params)
{
	return 0;
}

void run(ListMP* limp)
{
	char cmd[MAX_CMD_LEN];
	size_t cmd_length = 0, command_index = 0;

	//COMMANDS 
	char* menu = "\nadd - Adds <materie_prima>\nmodify - Modifies <materie_prima>\ndel - Deletes <materie_prima>\n\n";

	char* commands[MAX_CMD_LEN] = { "add", "modify", "del", "c_view", "o_view" };

	int(*commander[NO_COMMANDS])(ListMP* limp, char* params) = { ui_add, ui_modify, ui_del, ui_c_view, ui_o_view };

	//PARAMS
	char params[PARAMS_L];
	size_t params_length = 0;

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