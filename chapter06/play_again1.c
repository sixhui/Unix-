#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want another transaction"

int get_response(char*);
int set_crmode();
int tty_mode(int);

/**
 * @brief char-by-char mode, instant response
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    int response;
    tty_mode(0);                        // save
    
    set_crmode();                       // set
    response = get_response(QUESTION);
    
    tty_mode(1);                        // restore
    return response;
}

int get_response(char* question){
    int input;
    printf("%s(y/n)?", question);
    while(1){
        switch(input = getchar()){
            case 'y':
            case 'Y': return 0;
            case 'n':
            case 'N':
            case EOF: return 1;
            default:
                printf("\ncannot understand %c,", input);
                printf("Please type y or n \n");
        }
    }
}

int set_crmode(){
/**
 * @brief 
 * purpose: put file descriptor 0(i.e. stdin) into char-by-char mode
 * method: use bits in termios
 */
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}

int tty_mode(int how){
    static struct termios original_mode;
    if(how == 0)
        tcgetattr(0, &original_mode);
    else
        return tcsetattr(0, TCSANOW, &original_mode);
}