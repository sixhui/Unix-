#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ish3.h"



char* next_cmd(char* prompt, FILE* fd){
/**
 * purpose: read cmd line from fd
 * returns: dynamically allocated string holding cmd line
 * errors : NULL at EOF
 *          calls fatal from emalloc()
 * notes  : allocated space in BUFSIZE chunks
 */
    char    *buf;
    int     bufspace = 0;
    int     pos = 0;                        // 
    int     c;

    printf("%s", prompt);
    while((c = getc(fd)) != EOF){           // read by char
        // dynamically allocate space for char*
        if(pos + 1 >= bufspace){
            if(bufspace == 0)
                buf = malloc(BUFSIZ);
            else
                buf = realloc(buf, bufspace + BUFSIZ);
            bufspace += BUFSIZ;
        }

        // end of cmd?
        if(c == '\n') break;

        buf[pos++] = c;
    }

    if(c == EOF && pos == 0) return NULL;   // no input

    buf[pos] = '\0';
    return buf;
}

#define is_delim(x) ((x) == ' ' | (x) == '\t')
char** splitline(char* line){
/**
 * purpose: split a line into array
 * returns: a NULL-terminated array of pointers
 * actions: 
 * note: 
 * 
 */
    if(line == NULL) return NULL;

    char    **args;         // 字符串数组   - 用于返回
    int     spots = 0;      // 字符数       - 
    int     bufspace = 0;   // bit数       - 用于扩容
    int     argnum = 0;
    char    *cp = line;
    char    *start;
    int     len;

    char    *newstr();
    
    args    = emalloc(BUFSIZ);
    bufspace= BUFSIZ;
    spots   = BUFSIZ / sizeof(char*);

    while(*cp != '\0'){
        while(is_delim(*cp)) ++cp;
        if(*cp == "\0") break;

        // dynamically allocate space for char* []
        if(argnum + 1 >= spots){
            args    = erealloc(args, bufspace + BUFSIZ);
            bufspace+= BUFSIZ;
            spots   += (BUFSIZ / sizeof(char*));
        }

        // move & split
        start = cp;
        len = 1;
        while(*++cp != '\0' && !(is_delim(*cp))) ++len;
        args[argnum++] = newstr(start, len);
    }

    args[argnum] = NULL;
    return args;
}

char* newstr(char* s, int len){
    char* tmp = emalloc(len + 1);

    tmp[len] = '\0';
    strncpy(tmp, s, len);
    
    return tmp;
}

void freelist(char **list){
/**
 * purpose: free string list returned by splitline
 * 
 */
    char **cp = list;
    while(*cp) free(*cp++);
    free(list);
}

void *emalloc(size_t n){
    void *p;

    if((p = malloc(n)) == NULL)
        fatal("out of memory", "", 1);
    return p;
}

void *erealloc(void* p, size_t n){
    void *newp;
    
    if((newp = realloc(p, n)) == NULL)
        fatal("realloc() failed", "", 1);
    return newp;
}


// int main(int argc, char const *argv[])
// {
//     char* line;
//     while((line = next_cmd(">", stdin)) != NULL){
//         printf("%s\n", line);

//     }
//     return 0;
// }
