#include "../include/excuting.h"
#include "../include/parse.h"


int main(int argc,char **argv){
    struct command cmd[MAXLIST];
    char src[MAXCOM];
    char *shit[MAXCOM];
    int numCMD;
    while(1) {
        if (takeInput(src))
            continue;
        numCMD=processString(src,cmd);
        if(numCMD==1){
            execNonePipedCmd(cmd[0].cmd);
            numCMD=-1;
        } else {
        }
            execPipedCmd(cmd,numCMD);
    }
    write_history("/home/riadh/.testhis.txt");

}
