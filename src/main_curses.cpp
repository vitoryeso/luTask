#include <ncurses.h>
#include "luTaskWindows.h"
#include "luTask.h"

/* first lets make all windows */
int main(int argc, char** argv) {
    initscr(); 
    noecho();

    /* input window: initially is invisible. its be on center of the screen and gets inputs like new list names, task contents and tags */
    /* list window: show all pending tasks of a list. show only the begin os task contents. 3 windows list. */
    /* done window: its cool and beautiful. she lives on the right of the screen and and show all done tasks like a window list, but she have colors and blink all the time. */
    /* information window: lives on the bottom. show all the information about the list selected on the list window or the done window */
    /* other informations: 
     *      -two movement modes: vim and arrow keys
     *      -movement keys can jump inside a window, cant switch window using movement keys
     *      -SUPER movement keys: can be alt + movement keys or something like that
     *      -SUPER movement keys can move between windows
     *      -each window have a cursor.
     *      -we have boarders too. like trello, whe show the board name and can have background color or other things cool.
     */

    Board B;
    string filepath("checkpoint");
    if(!B.load(filepath)) {
        cout << "fail!" << endl;
        return -1;
    }
    BoardWin BW(stdscr, B);
    refresh();

    int c;
    while((c = BW.boardGetch()) != 27) {
        refresh();   
    }
    BW.write(filepath);

    endwin();
}
