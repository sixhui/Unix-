#include <stdio.h>
#include <signal.h>
#define INPUTLEN 100


int main(int argc, char const *argv[])
{
    struct sigaction newhandler;    // 信号配置
    sigset_t    blocked;            // 阻塞信号集
    void        inthandler();       // 信号处理函数
    char        x[INPUTLEN];

    newhandler.sa_handler = inthandler;
    
    
    
    
    return 0;
}
