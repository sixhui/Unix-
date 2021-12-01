#include <stdio.h>
#include <unistd.h>
#include <curses.h>

#define LEFTEDGE 10
#define RIGHTEDGE 30
#define ROW 10

int main(int argc, char const *argv[])
{
    const char* message    = "hello";
    const char* blank      = "      ";
    int dir         = 10;
    int pos         = LEFTEDGE;

    initscr();
    clear();

    int i = 3;
    while(i--){
        // show
        move(ROW, pos);
        addstr(message);
        move(LINES - 1, COLS - 1);
        refresh();
        sleep(1);

        // erase
        move(ROW, pos);
        addstr(blank);

        // move
        pos += dir;
        if(pos >= RIGHTEDGE)
            dir = -10;
        if(pos <= LEFTEDGE)
            dir = 10;

    }

    getch();
    endwin();
    
    
    return 0;
}
