#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


#define     MAXARGS     20
#define     ARGLEN      100

int main(int argc, char const *argv[])
{
    char    *arglist[MAXARGS + 1];
    int     numargs = 0;
    char    argbuf[ARGLEN];

    char    *makestring();
    int     execute();

    while(numargs < MAXARGS){
        printf("Arg[%d]?", numargs);
        if(fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
            arglist[numargs++] = makestring(argbuf);
        else{
            if(numargs > 0){
                arglist[numargs] = NULL;
                execute(arglist);
                numargs = 0;
            }
        }
    }
}


int execute(char* arglist[]){
    execvp(arglist[0], arglist);
    perror("execvp failed");
    exit(1);
}

char* makestring(char *buf){
    char *cp;
    buf[strlen(buf) - 1] = '\0';        // 去掉 \n

    cp = malloc(strlen(buf) + 1);
    if(cp == NULL){
        perror("no memory\n");
        exit(1);
    }
    strcpy(cp, buf);

    return cp;
}