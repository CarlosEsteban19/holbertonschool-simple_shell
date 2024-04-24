# holbertonschool-simple_shell
## Description
The shell is a program that takes commands from the keyboard and gives them to the operating system to perform. In the old days, it was the only user interface available on a Unix-like system such as Linux. In this case, our task was to recreate a minimalistic Unix command line interpreter that can be easily accesible.

## Installation
1- Clone repository  
> https://github.com/CarlosEsteban19/holbertonschool-simple_shell.git  

2- Compile files  
> gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

3- Run shell command   
> ./hsh  

## Libraries

#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/wait.h>  

## Use
The simple shell is a Unix command line interpreter.  
It will interpret the first word as a command, and the following as the series of arguments.

### Examples
ls
```
$ ls
functions.c hsh main.h README.md shell.c
$
```
echo
```
$ echo Hello World!
Hello World!
$
```
### For further help
For further help with the simple shell, and with which commands it runs; install our man page and run it with:  
```
man ./man_1_simple_shell
```
## Contributors
Carlos Esteban Colón Cintrón (<carlos-esteban.colon-cintron@holbertonstudents.com>)  
Louis Martínez Echevarría (<louis.martinez-echevarria@holbertonstudents.com>)
