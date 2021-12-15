#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if(argc != 2){
        perror("argc != 2\n");
        exit(1);
    }

    struct termios setting;
    tcgetattr(0, &setting);
    if(argv[1] == 0){
        setting.c_lflag |= ECHO;
    }
    else{
        setting.c_lflag &= ~ECHO;
    }
    
    tcsetattr(0, TCSANOW, &setting);


    
    return 0;
}
