#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void do_ls(const char[]);
void dostat(char* filename);
void show_file_info(char*, struct stat*);

int main(int argc, char const *argv[])
{

    if(argc == 1)
        do_ls(".");
    else
        while(--argc){
            printf("%s:\n", *++argv);
            do_ls(*argv);
        }
    
    return 0;
}

void do_ls(const char* dirname){
    DIR* dir_ptr;
    struct dirent *direntp;

    if((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls1: cannot open %s\n", dirname);
    else{
        while((direntp = readdir(dir_ptr)) != NULL)
            dostat(direntp->d_name);
        closedir(dir_ptr);
    }
}

void dostat(char* filename){
    struct stat info;
    if(stat(filename, &info) == -1)
        perror(filename);
    else
        show_file_info(filename, &info);
}

void show_file_info(char* filename, struct stat* info_p){
    char *uid_to_name(), *gid_to_name(), *ctime(), *filemode();
    void mode_to_letters();
    char modestr[11];

    mode_to_letters(info_p->st_mode, modestr);

    printf("%s", modestr);
    printf("%4d ", (int)info_p->st_nlink);
    printf("%-8s", uid_to_name(info_p->st_uid));
    printf("%-8s", gid_to_name(info_p->st_gid));
    printf("%8ld", (long)info_p->st_size);
    printf("%.12s ", 4 + ctime(&info_p->st_mtim));
    printf("%s\n", filename);

}

void mode_to_letters(int mode, char str[]){
    strcpy(str, "----------");

    if(S_ISDIR(mode)) str[0] = 'd';
    if(S_ISCHR(mode)) str[0] = 'c';
    if(S_ISBLK(mode)) str[0] = 'b';

    // 3 bits for user
    if(mode & S_IRUSR) str[1] = 'r';
    if(mode & S_IWUSR) str[2] = 'w';
    if(mode & S_IXUSR) str[3] = 'x';

    // 3 bits for group
    if(mode & S_IRGRP) str[4] = 'r';
    if(mode & S_IWGRP) str[5] = 'w';
    if(mode & S_IXGRP) str[6] = 'x';

    // 3 bits for other
    if(mode & S_IROTH) str[7] = 'r';
    if(mode & S_IWOTH) str[8] = 'w';
    if(mode & S_IXOTH) str[9] = 'x';

}

#include <pwd.h>
char* uid_to_name(uid_t uid){
    struct passwd *getpwuid(), *pw_ptr;
    static char numstr[10];

    if((pw_ptr = getpwuid(uid)) == NULL){
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    else
        return pw_ptr->pw_name;
}

#include <grp.h>
char* gid_to_name(gid_t gid){
    struct group * getgrgid(), *gr_ptr;
    static char numstr[10];

    if((gr_ptr = getgrgid(gid)) == NULL){
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else
        return gr_ptr->gr_name;
}

