#include "../include/excuting.h"

int execNonePipedCmd(char **str){

    // Forking a child
    pid_t pid = fork();

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




int execPipedCmd(struct command *cmd,int number_of_parsers) {




}






void runPipedCommands(struct command *cmd,int number_of_pipes) {


    int status;
    int i = 0;
    pid_t pid;

    int pipefds[2*number_of_pipes];

    for(i = 0; i < (number_of_pipes); i++){
        if(pipe(pipefds + i*2) < 0) {
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }
    }


    int j = 0;
    for(int n=0;n<number_of_pipes;n++) {
        pid = fork();
        if(pid == 0) {

            //if not last command
                if(dup2(pipefds[j + 1], 1) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            //if not first n!=0&& j!= 2*numPipes
            if(j != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    perror(" dup2");///j-2 0 j+1 1
                    exit(EXIT_FAILURE);

                }
            }


            for(i = 0; i < 2*number_of_pipes; i++){
                    close(pipefds[i]);
            }

            if( execvp(cmd[n].cmd[0], cmd[n].cmd) < 0 ){
                    exit(EXIT_FAILURE);
            }
        } else if(pid < 0){
            perror("error");
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
