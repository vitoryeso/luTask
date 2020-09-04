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
    void print(unsigned selectedTask, unsigned selectedList, Board &B, bool watch, bool dones) const;
    void printEmpty() const;

    inline void erase() {werase(curWin);}
};

class BoardWin {
private:
    WINDOW* infoWin;
    WINDOW* inputWin;
    WINDOW* confirmWin;
    TaskWin listWin, doneWin;
    Board B;
    unsigned xMax, yMax;
    unsigned x, y;
    unsigned selectedList;
    unsigned selectedListTask, selectedDoneTask;
    bool listOrDones; /* this bool represents where search the selected Task */

public:
    BoardWin(WINDOW* standard, Board& B); 

    /* ### CONFIRMATION WINDOW ### */
    /* this window confirm if user really want delete a task or list */
    void initConfirmWin(unsigned W);
    void drawConfirmWin(string title, bool selectedOption);
    bool confirmDelete(bool listOrTask);

    inline void write(string filepath) const {B.write(filepath);}

    /* ### INPUT WINDOW ### */
    void initInputWin();/* for input window, init screen make the border. just init a window */
    void drawInputBox(string title);
    string getData(string title);

    /* ### INFORMATION WINDOW ### */
    void initInfoWin();
    void printInfoWin();

    /* ### DONES WINDOW ### */
    WINDOW* initDoneWin();
    inline void printDoneWin() {doneWin.print(selectedDoneTask, selectedList, B, !listOrDones, true);}

    /* ### LISTS WINDOW ### */
    WINDOW* initListWin();
    void printListWin();

    /* show input window, get task, add task and hide input window */
    void addTask();
    void addList();

    void renameTask();
    void renameList();


    /* get user input from the current window, make changes in the object and prints all the content.
     * returns the same integer returned by the wgetch function. */
    int boardGetch();
};

#endif
