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
#define FD_READ 0
#define FD_WRITE 1

#include "./parse.h"
int execNonePipedCmd(char **str);
int execPipedCmd(struct command *cmd,int number_of_pipes);
int execNonePipedDemondCmd(char **str);
#endif

