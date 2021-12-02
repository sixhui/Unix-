#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// ps -e 将看到两个进程，使用同一个终端 TTY
int main(int argc, char const *argv[])
{
    int res_from_fork;

    printf("Before: pid %d\n", getpid());

    res_from_fork = fork();

    sleep(10);
    printf("After: pid %d - fork return %d\n", getpid(), res_from_fork);
    
    
    
    return 0;
}
