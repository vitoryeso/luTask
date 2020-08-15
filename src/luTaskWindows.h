#ifndef LU_TASK_WINDOWS_H
#define LU_TASK_WINDOWS_H

#include <ncurses.h>
#include "luTask.h"

/* generic class for show tasks in ncurses windows */
class TaskWin {
private:
    WINDOW* curWin;
    unsigned xMax, yMax;
public:
    TaskWin(): curWin(NULL), xMax(0), yMax(0) {}
    TaskWin(WINDOW* standard); 

    inline int TaskWinGetch() {return wgetch(curWin);}

    /* print tasks by the selected reference */
    void print(unsigned selectedTask, TaskList& TL, bool watch) const;

    inline void erase() {werase(curWin);}
};

class BoardWin {
private:
    WINDOW* infoWin;
    WINDOW* inputWin;
    TaskWin listWin, doneWin;
    Board B;
    unsigned xMax, yMax;
    unsigned x, y;
    unsigned selectedList;
    unsigned selectedListTask, selectedDoneTask;
    bool listOrDones; /* this bool represents where search the selected Task */

public:
    BoardWin(WINDOW* standard, Board& B); 

    /* for input window, init screen make the border. just init a window */
    void initInputWin();

    void initInfoWin();
    WINDOW* initDoneWin();
    WINDOW* initListWin();

    void drawInputBox(string title);
    string getData(string title);
    /* show input window, get task, add task and hide input window */
    void addTask();

    void printInfoWin();
    inline void printDoneWin() {doneWin.print(selectedDoneTask, B.getDones(), !listOrDones);}
    inline void printListWin() {listWin.print(selectedListTask, B.getList(selectedList), listOrDones);}

    /* get user input from the current window, make changes in the object and prints all the content.
     * returns the same integer returned by the wgetch function. */
    int boardGetch();
};

#endif
