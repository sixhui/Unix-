#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/**
 * alarm() + signal() + pause()
 */
int main(int argc, char const *argv[])
{
    void wakeup(int);

    printf("about to sleep for 4s\n");
    signal(SIGALRM, wakeup);
    alarm(4);
    pause();
    printf("bye\n");
    
    
    return 0;
}

void wakeup(int signum){
    printf("SIGALRM received from kernel\n");
}

