#include <stdio.h>
#include <termios.h>


#define QUESTION "Do you want another transcation"

int get_response(char*);
int set_cr_noecho_mode();
int tty_mode();

/**
 * @brief 取消回显
 * 
 */
int main(int argc, char const *argv[])
{
    int response;
    tty_mode(0);    // save mode
    
    set_cr_noecho_mode();
    response = get_response(QUESTION);
    
    tty_mode(1);    // restore mode
    return response;
}

int get_response(char* question){
    printf("%s (y/n)?", question);
    while(1){
        switch(getchar()){
            case 'y':
            case 'Y': return 0;
            case 'n':
            case 'N':
            case EOF: return 1;
        }
    }
}

// put fd 0 into char-by-char mode and noecho mode
int set_cr_noecho_mode(){
    struct termios ttystate;
    tcgetattr(0, &ttystate);

    ttystate.c_lflag &= ~ICANON;    // no buffering
    ttystate.c_lflag &= ~ECHO;      // no echo
    ttystate.c_cc[VMIN] = 1;        // get 1 char at a time

    tcsetattr(0, TCSANOW, &ttystate);
}
// 
int tty_mode(int how){
    static struct termios original_mode;
    
    if(how == 0)
        tcgetattr(0, &original_mode);
    else
        return tcsetattr(0, TCSANOW, &original_mode);
}