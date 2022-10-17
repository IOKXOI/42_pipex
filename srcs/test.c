#include "pipex.h"

void print_commands(t_elements *elements)
{
	int i;

	i = 0;
	printf("PATHS : \n");
	while (elements->paths[i])
	{
		printf("%s ", elements->paths[i]);
		printf("\n");
		i++;
	}
	i = 0;
	printf("COMMANDS : \n");
	while (elements->node_commands)
	{
		while(elements->node_commands->commands[i])
		{
			printf("%s ",elements->node_commands->commands[i]);
			printf("\n");
			i++;
		}
		i = 0;
		elements->node_commands = elements->node_commands->next;
	}
}
