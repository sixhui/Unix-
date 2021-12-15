#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

#define oops(s, x){perror(s); exit(x);}

int main(int argc, char const *argv[])
{
    struct termios setting;
    if(argc == 1) exit(0);

    if(tcgetattr(0, &setting) == -1) oops("tcgetattr", 1);
    
    if(argv[0][1] == 'y') setting.c_lflag |= ECHO;
    else setting.c_lflag &= ~ECHO;

    if(tcsetattr(0, TCSANOW, &setting) == -1) oops("tcsetattr", 1);
    
    
    return 0;
}
