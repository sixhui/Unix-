#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

#define ASK "Do you want another transaction"
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a')

int tty_mode(int);
int set_cr_noecho_mode();
int set_nodelay_mode();
int get_response(char*, int);
int get_ok_char();

/**
 * @brief 非阻塞输入：检查是否有输入，没有则睡眠几秒，然后继续检查，尝试 3 次后放弃
 * 
 * 驱动程序缓冲输出，直到收到一个换行符，或程序试图从终端读取输入，所以使用 fflush 强制输出
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    int response;
    tty_mode(0);
    
    set_cr_noecho_mode();
    set_nodelay_mode();
    response = get_response(ASK, TRIES);
    
    tty_mode(1);
    return response;
}

int get_response(char* question, int maxtries){
    int input;
    printf("%s (y/n)?", question);
    fflush(stdout);
    while(1){
        sleep(SLEEPTIME);
        input = tolower(get_ok_char());
        if(input == 'y')
            return 0;
        if(input == 'n')
            return 1;
        if(maxtries-- == 0)
            return 2;
        BEEP;
    }
}

// 获取合法字符
int get_ok_char(){
    int c;
    while((c = getchar()) != EOF && strchr("yYnN", c) == NULL);
    return c;
}

int set_cr_noecho_mode(){
    struct termios ttystate;
    tcgetattr(0, &ttystate);

    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    
    tcsetattr(0, TCSANOW, &ttystate);
}

int set_nodelay_mode(){
    int termflags;
    termflags = fcntl(0, F_GETFL);
    termflags |= O_NDELAY;
    fcntl(0, F_SETFL, termflags);
}

int tty_mode(int how){
    static struct termios original_mode;
    static int original_flags;

    if(how == 0){
        tcgetattr(0, &original_mode);
        original_flags = fcntl(0, F_GETFL);
    }
    else{
        tcsetattr(0, TCSANOW, &original_mode);
        fcntl(0, F_SETFL, original_flags);
    }

}