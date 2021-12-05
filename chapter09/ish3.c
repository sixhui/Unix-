/**
 * 用户按下 CTRL-d 或输入 exit 退出程序
 * 用户能在一行中输入所有参数
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ish3.h"

#define DFL_PROMPT ">"

int main(int argc, char const *argv[])
{
    char    *cmdline, *prompt, **arglist;
    int     result;

    void    setup();

    // initialize shell
    prompt  = DFL_PROMPT;
    setup();                                                

    while((cmdline = next_cmd(prompt, stdin)) != NULL){     // 输入流读取命令
        if((arglist = splitline(cmdline)) != NULL){         // 分解命令字符串
            result = execute(arglist);                      // 执行命令
            freelist(arglist);
        }
        free(cmdline);
    }
    return 0;
}

void setup(){
/**
 * purpose: initialize shell
 */
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void fatal(char* s1, char* s2, int n){
    fprintf(stderr, "Error: %s, %s\n", s1, s2);
    exit(n);
}

