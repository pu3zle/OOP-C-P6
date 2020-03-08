#include "service.h"
#include "ui.h"


#define MAX_CMD_LEN 30
#define NO_COMMANDS 5
#define PARAMS_L 20


int read_command(char* buffer)
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
	buffer[i] = NULL;
	if (i == 0)
		return -1;
	if (stream_length > MAX_CMD_LEN)
		return -1;
	return i;
}

void get_params(char* cmd, char* params, int cmd_length, int* params_length)
{
	for (size_t i = 0; i < cmd_length; i++)
	{
		if (cmd[i] == ' ')
		{
			char* from_where = cmd + i + 1;
			strncpy(params, from_where, PARAMS_L);
			*params_length = cmd_length - i;
			return;

		}
	}
}

int validate_command(char* buffer, char* commands[MAX_CMD_LEN])
{
	for (size_t i = 0; i < NO_COMMANDS; i++)
	{
		if (strcmp(buffer, commands[i]) == 0)
			return i;
	}
	return -1;
}

//IMPLEMENT THE FUNCTIONS
void ui_add(char* params)
{}
void ui_modify(char* params)
{}
void ui_del(char* params)
{}
void ui_c_view(char* params)
{}
void ui_o_view(char* params)
{}

void run()
{
	char cmd[MAX_CMD_LEN];
	int cmd_length = 0, command_index = 0;

	//COMMANDS 
	char* menu = "\nadd - Adds <materie_prima>\nmodify - Modifies <materie_prima>\ndel - Deletes <materie_prima>\n\n";

	char* commands[MAX_CMD_LEN] = { "add", "modify", "del", "c_view", "o_view" };

	void(*commander[NO_COMMANDS])(char* params) = { ui_add, ui_modify, ui_del, ui_c_view, ui_o_view };

	//PARAMS
	char params[PARAMS_L];
	int params_length = 0;

	while (true)
	{
		_write(1, ">>", 2);
		cmd_length = read_command(cmd);
		
		if (cmd[0] == '\n')continue;

		if (cmd_length != -1)
		{
			if (strcmp(cmd, "help") == 0)
				printf("%s", menu);

			command_index = validate_command(cmd, commands);

			if (command_index != -1)
			{
				get_params(cmd, params, cmd_length, params_length);
				//CHECK PARAMS
				//VALIDATE 'EM
				commander[command_index](params);
			}
			else {
				printf("Unknown command!\nType \"help\" to see the commands!\n");
			}
		}
		else
			printf("Unknown command!\nType \"help\" to see the commands!\n");
	}
		
}