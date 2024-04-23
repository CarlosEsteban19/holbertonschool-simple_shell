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
			printf("\n");
			break; /*eof (ctrl+D)*/
		}
		/* trim trailing newline*/
		if (input[strlen(input)] == '\n')
			input[strlen(input)] = '\0';
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
			else
				(execute_or_find_command(args));
		}
		free(args);
	}
	return (0);
}
