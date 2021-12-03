#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define     MAXARGS     20      // 最大命令参数个数
#define     ARGLEN      100     // 最大命令长度


int main(int argc, char const *argv[])
{
    char    *arglist[MAXARGS];  // 参数数组
    int     numargs = 0;        // 参数个数
    char    argbuf[ARGLEN];     // 参数 BUF
    char    *makestring();      // 参数 BUF -> 参数数组
    int     execute();          // 执行命令 - execvp

    while(numargs < ARGLEN){
        printf("Arg[%d]?", numargs);
        // 获取参数
        if(fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n'){
            arglist[numargs++] = makestring(argbuf);
        }

        // 执行命令
        else{
            if(numargs == 0) continue;

            arglist[numargs] = NULL;
            execute(arglist);
            numargs = 0;        // 重置
        }
    }
    
    return 0;
}

// copy buf
char* makestring(char* buf){
    char* cp;

    buf[strlen(buf) - 1] = '\0';    // trim '\n'
    cp = malloc(strlen(buf) + 1);

    if(cp == NULL){
        perror("no memory\n");
        exit(1);
    }

    strcpy(cp, buf);
    return cp;
}

// 执行命令
int execute(char* arglist[]){
    int pid, exit_status;

    pid = fork();
    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        
        // 子进程
        case 0: 
            execvp(arglist[0], arglist);
            perror("execvp failed");
            exit(1);
        
        // 父进程
        default: 
            while(wait(&exit_status) != pid);
            printf("child exited with status %d, %d\n", exit_status >> 8, exit_status & 0377);
    }
}