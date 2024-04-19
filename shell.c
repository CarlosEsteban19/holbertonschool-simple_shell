#include "main.h"
/**
 * main - entry point, command line interpreter
 * Return: always 0 on success or Error cases
 */
int main(void)
{
	char **args;
	char *input = NULL;
	size_t bufsize = 0;

	while (1)
	{
		if (isatty(fileno(stdin)))
			printf("$ ");
		if (getline(&input, &bufsize, stdin) == -1)
		{
			free(input);
			input = NULL;
			printf("\n");
			break; /*eof (ctrl+D*/
		}
		input[strcspn(input, "\n")] = '\0'; /*trim trailing '\n'*/
		args = parse_input(input); /*tokenize user input*/
		if (args == NULL)
		{
			free(input);
			continue;
		}
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free(input);
				free(args);
				break;  /*Exit the shell*/
			}
			if (execute_or_find_command(args) != 0)
				printf("Error executing command.\n");
		}
		free(args);
	}
	return (0);
}