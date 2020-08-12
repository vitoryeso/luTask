#include "luTaskWindows.h"

TaskWin::TaskWin(WINDOW* standard) {
    curWin = standard;
    getmaxyx(curWin, yMax, xMax);    
}

void TaskWin::print(unsigned selectedTask, TaskList& TL, bool watch) const {
    /* we can print task in cursors with Y_position between 1 and (yMax - 1) */
    unsigned realHeight = yMax - 2;

    /* we can print all tasks with no problems */
    if(TL.getSize() <= realHeight) {
        for(unsigned i=0; i<TL.getSize(); i++) {
            wmove(curWin, i + 1, 1);
            if(i == selectedTask && watch) wattron(curWin, A_REVERSE);
            wprintw(curWin, TL.getTask(i).getContent().c_str());
            wattroff(curWin, A_REVERSE);
        }
    }
    else {
        /* printing in reversed direction from selectedTask*/
        unsigned diff(selectedTask - realHeight);
        for(unsigned i=selectedTask; i>diff; i--) {
            wmove(curWin, realHeight + 1 - (selectedTask - i), 1);
            if(i == selectedTask && watch) wattron(curWin, A_REVERSE);
            wprintw(curWin, TL.getTask(i).getContent().c_str());
            wattroff(curWin, A_REVERSE);
        }
    }
    wborder(curWin, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
    wrefresh(curWin);
}

BoardWin::BoardWin(WINDOW* standard, Board& B) {
    this->B = B;
    x = y = 1;
    selectedListTask = selectedDoneTask = 0;
    selectedList = 0;
    listOrDones = true;
    getmaxyx(standard, yMax, xMax);
    initInfoWin();
    doneWin = TaskWin(initDoneWin());
    listWin = TaskWin(initListWin()); 

    wmove(infoWin, 7, 20);
    wprintw(infoWin, "selectedList: %d, selectedListTask: %d, selectedDoneTask: %d, listOrDones: %d", selectedList, selectedListTask, selectedDoneTask, listOrDones);
    listWin.erase();
    printListWin();
    werase(infoWin);
    printInfoWin();
}

WINDOW* BoardWin::initDoneWin() {
    unsigned listWinHeight = yMax*0.75;
    unsigned listWinWidth = (xMax / 2) - 1;
    WINDOW* doneWin = newwin(listWinHeight, listWinWidth + 1, 1, listWinWidth);
    refresh();

    wborder(doneWin, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
    wrefresh(doneWin);

    return doneWin;
}

void BoardWin::initInfoWin() {
    unsigned infoWinHeight = (yMax*0.25);
    infoWin = newwin(infoWinHeight, xMax - 2, yMax - infoWinHeight, 1); 
    refresh();

    wborder(infoWin, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
    wrefresh(infoWin);
}

WINDOW* BoardWin::initListWin() {
    unsigned listWinHeight = yMax*0.75;
    unsigned listWinWidth = (xMax / 2) - 1;
    WINDOW* listWin = newwin(listWinHeight, listWinWidth, 1, 1);
    refresh();

    wborder(listWin, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
    wrefresh(listWin);

    return listWin;
}

void BoardWin::printInfoWin() {
    if(!listOrDones) {
        Task T = B.getDones().getTask(selectedDoneTask);
        wmove(infoWin, 1, 1);
        wprintw(infoWin, T.getContent().c_str()); 
        wmove(infoWin, 2, 1);
        wprintw(infoWin, ("Tag: " + T.getTag()).c_str()); 
        wmove(infoWin, 3, 1);
        wprintw(infoWin, ("Init Date: " + T.getInitDate().getStr()).c_str());
        wmove(infoWin, 4, 1);
        wprintw(infoWin, ("Finish Date: " + T.getFinishDate().getStr()).c_str());
    }
    else {
        Task T = B.getList(selectedList).getTask(selectedListTask);
        wmove(infoWin, 1, 1);
        wprintw(infoWin, T.getContent().c_str()); 
        wmove(infoWin, 2, 1);
        wprintw(infoWin, ("Tag: " + T.getTag()).c_str()); 
        wmove(infoWin, 3, 1);
        wprintw(infoWin, ("Init Date: " + T.getInitDate().getStr()).c_str());
    }
    wborder(infoWin, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
    wrefresh(infoWin);
}

int BoardWin::boardGetch() {
    int c;
    if(!listOrDones) c = doneWin.TaskWinGetch(); 
    else c = listWin.TaskWinGetch(); 
    switch(c) {
        case 104: //h
            if(selectedList > 0 && listOrDones) {
                selectedList--;
                selectedListTask = 0;
            }
            break;

        case 106: //j
            if(!listOrDones && selectedDoneTask < B.getDones().getSize() - 1){
                selectedDoneTask++; 
            }
            else if(listOrDones && selectedListTask < B.getList(selectedList).getSize() - 1) {
                selectedListTask++;
            }
            break;

        case 107: //k
            if(!listOrDones && selectedDoneTask > 0){
                selectedDoneTask--; 
            }
            else if(listOrDones && selectedListTask > 0) {
                selectedListTask--;
            }
            break;

        case 108: //l
            if((selectedList < (B.getNumLists() - 1)) && listOrDones) {
                selectedList++;
                selectedListTask = 0;
            }
            break;

        case 72: //H
            if(!listOrDones) listOrDones = true;
            break;

        case 76: //L
            if(listOrDones) listOrDones = false;
            break;

        default:
            break;
    }
    wmove(infoWin, 7, 20);
    wprintw(infoWin, "selectedList: %d, selectedListTask: %d, selectedDoneTask: %d, listOrDones: %d", selectedList, selectedListTask, selectedDoneTask, listOrDones);
    doneWin.erase();
    printDoneWin();
    listWin.erase();
    printListWin();
    werase(infoWin);
    printInfoWin();

    return c;
}
