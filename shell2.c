#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10
/**
 * _getenv - gets envitoment
 * @name: name of enviroment variable
 * Return: value after =, or NULL
 */
char *_getenv(const char *name)
{
	extern char **environ;
	size_t name_len = strlen(name);
	char **env = environ;

	while (*env != NULL)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
			return (&(*env)[name_len + 1]); /*Return the value after '='*/
		env++;
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
		args[num_args++] = token;
		token = strtok(NULL, " \n");
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
		if (execute_command(args) != 0)
			printf("Error executing command.\n");
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
				if (execute_command(args) != 0)
					printf("Error executing command.\n");
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
