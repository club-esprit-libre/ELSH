#include "../include/excuting.h"
#include "../include/parse.h"

int main(int argc,char **argv){
    struct command cmd[MAXLIST];
    char src[MAXCOM];
    char *shit[MAXCOM];
    int numCMD;
    char history_file[1024]= "/home/";
    strcat(history_file,getenv("USER"));
    strcat(history_file,"/.test.txt");
    using_history();
    read_history(history_file);
    while(1) {
        if (takeInput(src))
            continue;
        numCMD=processString(src,cmd);
        switch(numCMD) {
            case 3:
                execNonePipedBackgroundCmd(cmd[0].cmd);
            break;
            case 2:
                execPipedBackgroundCmd(cmd,numCMD);
            break;
            case -1:
            break;
            case 0:
            break;
            case 1:
                execNonePipedCmd(cmd[0].cmd);
            break;
            default:
                execPipedCmd(cmd,numCMD);
            break;
        }
    }

}
