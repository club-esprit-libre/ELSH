#ifndef EXEC
#define EXEC
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#include "./parse.h"
int execNonePipedCmd(char **str);
int execPiepedCmd(struct command *cmd,int number_of_pipes);
#endif

