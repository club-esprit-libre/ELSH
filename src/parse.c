#include "../include/parse.h"
#include "../include/nerdfondticons.h"

void openHelp()
{
    puts("\n***WELCOME TO MY SHELL HELP***"
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>exit"
        "\n>all other general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>improper space handling");

    return;
}

int ownCmdHandler(char** parsed)
{
    char history_file[1024]= "/home/";
    strcat(history_file,getenv("USER"));
    strcat(history_file,"/.test.txt");
    int NoOfOwnCmds = 4, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;
    char *cmd[MAXLIST];
    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "hello";

    for (i = 0; i < NoOfOwnCmds; i++) {
        cmd[i]=parsed[i];
        if (strcmp(parsed[0],ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg) {
    case 1:
        printf("\nGoodbye\n");
        write_history(history_file);
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        openHelp();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n",
            username);
        return 1;
    default:
        break;
    }

    return 0;
}


int takeInput(char* str)
{
    char bar[1024]="\n";
    strcat(bar,nf_custom_folder_open);
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    strcat(bar," ");
    strcat(bar,cwd);
    strcat(bar," ");
    strcat(bar,nf_fa_angle_double_right);
    strcat(bar," ");
    char* buf;
    buf = readline(bar);
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str,buf);
        return 0;
    } else {
        return 1;
    }
}


int parsePipe(char* str, char** strpiped) {
    int i=0;
        strpiped[i] = strtok(str, "|");
    while(strpiped[i] != NULL) {
        i++;
        strpiped[i] = strtok(NULL, "|");
    }
    return i;
}




int findspecificChar(char *str) {
    if(strchr(str,'&')!=NULL)
        return 0;
    else if(strchr(str,';')!=NULL)
        return 1;
    else if(strchr(str,'\\')!=NULL)
        return 2;
    else
        return -1;
}





void parseSpace(char* str, char** cmd)
{

    int i=0;
        cmd[i] = strtok(str, " ");
    while(cmd[i] != NULL) {
        i++;
        cmd[i] = strtok(NULL, " ");
    }
}





int processString(char* str,struct command *cmd){
    char* strpiped[MAXLIST];

    int piped = 0;

    piped = parsePipe(str, strpiped);
    if (piped > 1) {
        for(int i=0;i<piped;i++){
            parseSpace(strpiped[i], cmd[i].cmd);
        }
    }
    else {
        parseSpace(str, cmd[0].cmd);
    }
    if(ownCmdHandler(cmd[0].cmd))
        return 0;
    return piped;
}


