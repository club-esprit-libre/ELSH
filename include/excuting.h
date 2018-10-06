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
#include <fcntl.h>
#include "./parse.h"

int execNonePipedCmd(char **str);
int execPipedCmd(struct command *cmd,int number_of_pipes);
int execNonePipedBackgroundCmd(char **str);
int  execPipedBackgroundCmd(struct command *cmd,int number_of_pipes);

#endif
