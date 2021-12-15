#include <stdio.h>
// #include <termio.h>

#define QUESTION "Do you want another transaction"


int get_response(char*);

/**
 * @brief play_again0.c
 * purpose: ask if user wants another transaction
 * method:  ask a question, wait for yes/no answer
 * @return 0 -> yes, 1 -> no 
 * better: eliminate need to press Enter
 */
int main(int argc, char const *argv[])
{
    int response;
    response = get_response(QUESTION);
    
    
    return response;
}

int get_response(char* question){
    printf("%s(y/n)?", question);
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