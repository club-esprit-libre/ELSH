#include "../include/excuting.h"

int execNonePipedCmd(char **str){

    // Forking a child
    pid_t pid = vfork();

    if (pid == -1) {
        printf("\nFailed forking child..");
        return 0;
    } else if (pid == 0) {
        if (execvp(str[0],str) < 0) {
            printf("\nCould not execute command..");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL);
        return 1;
    }
}


int execNonePipedBackgroundCmd(char **str){

    // Forking a child
    pid_t pid = vfork();

    if (pid == -1) {
        printf("\nFailed forking child..");
        return 0;
    } else if (pid == 0) {
        execvp(str[0],str);
        perror("execute");
        exit(EXIT_SUCCESS);

    }
}








int  execPipedCmd(struct command *cmd,int number_of_pipes) {

      int status;
    int i = 0;
    pid_t pid;

    int pipefds[2*number_of_pipes];

    for(i = 0; i < (number_of_pipes); i++){
        if(pipe(pipefds + i*2) < 0) {
            exit(EXIT_FAILURE);
        }
    }
    int commandc=0;

    int j = 0;
    for(commandc=0;commandc<number_of_pipes;commandc++) {
        pid = vfork();
        if(pid == 0) {

            //if not last command
            if(commandc!=number_of_pipes-1){
                if(dup2(pipefds[j + 1], 1) < 0){
                    exit(EXIT_FAILURE);
                }
            }

            //if not first command&& j!= 2*numPipes
            if(j != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    exit(EXIT_FAILURE);

                }
            }


            for(i = 0; i < 2*number_of_pipes; i++){
                    close(pipefds[i]);
            }

            if( execvp(cmd[commandc].cmd[0], cmd[commandc].cmd) < 0 ){
                    exit(EXIT_FAILURE);
            }
        } else if(pid < 0){
            exit(EXIT_FAILURE);
        }

        j+=2;
    }
    /**Parent closes the pipes and wait for children*/

    for(i = 0; i < 2 * number_of_pipes; i++){
        close(pipefds[i]);
    }

    for(i = 0; i < number_of_pipes + 1; i++)
        wait(&status);
}






int  execPipedBackgroundCmd(struct command *cmd,int number_of_pipes) {

      int status;
    int i = 0;
    pid_t pid;

    int pipefds[2*number_of_pipes];

    for(i = 0; i < (number_of_pipes); i++){
        if(pipe(pipefds + i*2) < 0) {
            exit(EXIT_FAILURE);
        }
    }
    int commandc=0;

    int j = 0;
    for(commandc=0;commandc<number_of_pipes;commandc++) {
        pid = vfork();
        if(pid == 0) {

            //if not last command
            if(commandc!=number_of_pipes-1){
                if(dup2(pipefds[j + 1], 1) < 0){
                    exit(EXIT_FAILURE);
                }
            }

            //if not first command&& j!= 2*numPipes
            if(j != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    exit(EXIT_FAILURE);

                }
            }


            for(i = 0; i < 2*number_of_pipes; i++){
                    close(pipefds[i]);
            }

            if( execvp(cmd[commandc].cmd[0], cmd[commandc].cmd) < 0 ){
                    exit(EXIT_FAILURE);
            }
        } else if(pid < 0){
            exit(EXIT_FAILURE);
        }

        j+=2;
    }
    /**Parent closes the pipes and wait for children*/

    for(i = 0; i < 2 * number_of_pipes; i++){
        close(pipefds[i]);
    }

    for(i = 0; i < number_of_pipes; i++)
        wait(&status);
}






