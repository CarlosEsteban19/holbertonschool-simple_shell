#include "main.h"
/**
 * _getenv - gets envitoment
 * @name: name of enviroment variable
 * Return: value after =, or NULL
 */
char *_getenv(const char *name)
{
	int i;
	static struct env_var enviroment[] = {
		{"PATH", "/usr/bin:/bin"},
		/*add more enviroment variables here*/
		{NULL, NULL}
	};

	for (i = 0; enviroment[i].name != NULL; i++)
	{
		if (strcmp(enviroment[i].name, name) == 0)
			return (enviroment[i].value);
	}
	return (NULL); /*Environment variable not found*/
}
/**
 * parse_input - analyses user input and tokenizes
 * @input: user input string
 * Return: array of tokens
 */
char **parse_input(char *input)
{
	char **args = malloc(MAX_ARGS * sizeof(char *));
	char *token;
	int num_args = 0;

	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token = strtok(input, " \n");
	while (token != NULL && num_args < MAX_ARGS - 1)
	{
		args[num_args] = token;
		token = strtok(NULL, " \n");
		num_args++;
	}
	args[num_args] = NULL;
	return (args);
}
/**
 * execute_command - forks process, executes command and waits if necesary
 * @args: array of tokens with command & arguments
 * Return: -1 on fork error, or 0 success
 */
int execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0) /*Child process*/
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else /*Parent process*/
	{
		wait(NULL);
	}
	return (0);
}
/**
 * execute_or_find_command - checks command input for execution
 * @args: array of tokens with args[0] being the command
 * Return: -1 if command not found, 0 on success
 */
int execute_or_find_command(char **args)
{
	/* Check if the command is a full path */
	if (access(args[0], X_OK) == 0)
	{
		execute_command(args);
	}
	else
	{
		/* Check if the command exists in PATH */
		char *path = _getenv("PATH");
		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");

		while (dir != NULL)
		{
			char *command_path = malloc(strlen(dir) + strlen(args[0]) + 2);

			sprintf(command_path, "%s/%s", dir, args[0]);
			if (access(command_path, X_OK) == 0)
			{
				args[0] = command_path; /* Update command with full path */
				execute_command(args);
				free(command_path);
				free(path_copy);
				return (0); /*Command found and executed successfully*/
			}
			free(command_path);
			dir = strtok(NULL, ":");
		}
		free(path_copy);
		printf("Command not found: %s\n", args[0]);
		return (-1); /*Command not found*/
	}
	return (0); /*Command executed successfully*/
}
