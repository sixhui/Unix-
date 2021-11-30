#include <sys/stat.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
    struct stat sp;

    if(stat("/etc/passwd", &sp)){
        perror("/etc/passwd\n");
    }
    else{
        printf("mode: %ox\n", sp.st_mode);
        printf("links: %d\n", sp.st_nlink);
        printf("user: %d\n", sp.st_uid);
        printf("group: %d\n", sp.st_gid);
        printf("size %d\n", sp.st_size);
        printf("modtime %d\n", sp.st_mtim);
    }


    
    
    
    return 0;
}
