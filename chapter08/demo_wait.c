#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define     DELAY   20

int main(int argc, char const *argv[])
{
    int newpid;
    void child_code(), parent_code();

    if((newpid = fork()) == -1)
        perror("fork error");
    else if(newpid == 0)
        child_code(DELAY);
    else 
        parent_code();
    
    return 0;
}

void child_code(int delay){
    printf("child %d: sleep for %d seconds\n", getpid(), delay);
    sleep(delay);
    printf("child done\n");
    exit(4);
}

void parent_code(){
    int chld_pid, chld_status;
    int high_8, low_1, low_7;

    chld_pid = wait(&chld_status);
    printf("done wait for %d\n", chld_pid);

    high_8  = chld_status >> 8;
    low_1   = chld_status & 0x80;
    low_7   = chld_status & 0x7F;
    printf("status: exit = %d, core = %d, sig = %d\n", high_8, low_1, low_7);




}