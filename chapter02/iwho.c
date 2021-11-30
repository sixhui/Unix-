#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
// #include <sys/time.h>
#include <time.h>

int main(int argc, char const *argv[])
{

    
    struct timeval t;
    time_t p = time(NULL);
    
    char* cp = ctime(&p);
    printf("%s", cp);
    
    gettimeofday(&t, NULL);
    printf("%d\n", p);
    printf("%d\n", t.tv_sec);

    
    
    return 0;
}
