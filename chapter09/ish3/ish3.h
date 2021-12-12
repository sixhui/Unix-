




#define     YES     1
#define     NO      0

char    *next_cmd();
char    **splitline(char*);
int     execute(char**);

void    *emalloc(size_t);
void    *erealloc(void*, size_t);
void    freelist(char**);

void    fatal(char*, char*, int);