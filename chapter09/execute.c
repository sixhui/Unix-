#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "ish3.h"



int execute(char* argv[]){
/**
 * purpose: run a program
 * returns: status wait
 */
    int     pid;
    int     child_info = -1;

    if(argv[0] == NULL) return 0;

    if((pid = fork()) == -1) perror("fork fatal");
    // child
    else if(pid == 0){
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        execvp(argv[0], argv);

        perror("cannot execute command");
        exit(1);
    }
    // root
    else{
        if(wait(&child_info) == -1) perror("wait");
        return child_info;
    }



}