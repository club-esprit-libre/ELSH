#include "../include/excuting.h"
#include "../include/parse.h"

int main(int argc,char **argv){
    struct command cmd[MAXLIST];
    char src[MAXCOM];
    char *shit[MAXCOM];
    int numCMD;
    char history_file[1024]= "/home/";
    strcat(history_file,getenv("USER"));
    printf("%s\n",history_file);
    strcat(history_file,"/.test.txt");
    using_history();
    read_history(history_file);
    while(1) {
        if (takeInput(src))
            continue;
        numCMD=processString(src,cmd);
        if(numCMD==0){
            perror("ok");
            execNonePipedBackgroundCmd(cmd[0].cmd);
        }
        if(numCMD==1){
            execNonePipedCmd(cmd[0].cmd);
            numCMD=-1;
        } else {
        }
            execPipedCmd(cmd,numCMD);
    }

}
