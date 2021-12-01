#include <stdio.h>
#include <ctype.h>
/**
 * @brief rotate.c : map a->b b->c .. z->a
 * purpose: useful for showing tty modes
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    int c;
    while((c = getchar()) != EOF){
        if(c == 'z') c = 'a';
        else if(islower(c)) c++;
        putchar(c);
    }
    return 0;
}
