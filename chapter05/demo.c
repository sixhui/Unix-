#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    struct termios setting;

    if(tcgetattr(0, &setting) == -1) {
        perror("tcgetattr");
        exit(1);
    }
    
    if(setting.c_lflag & ECHO){
        printf("echo is on, since its bit is 1\n");
    }
    else{
        printf("echo is off, since its bit is 0\n");
    }
    
    return 0;
}
