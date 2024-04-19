#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10

struct env_var
{
char *name;
char *value;
};

char *_getenv(const char *name);
char **parse_input(char *input);
int execute_command(char **args);
int execute_or_find_command(char **args);

#endif /* MAIN_H */
