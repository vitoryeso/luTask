#include "luTaskWindows.h"

TaskWin::TaskWin(WINDOW* standard) {
    curWin = standard;
    getmaxyx(curWin, yMax, xMax);    
}

void TaskWin::printEmpty() const {
    wborder(curWin, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
    wrefresh(curWin);
}

void TaskWin::print(unsigned selectedTask, TaskList& TL, bool watch) const {
    if(TL.getSize() > 0) {
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
    }
    wborder(curWin, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
    wrefresh(curWin);
    string name(TL.getName());
    unsigned provx = (xMax/2) - name.length()/2;
    wattron(curWin, A_REVERSE);
    mvwprintw(curWin, yMax -1, provx, name.c_str());
    wattroff(curWin, A_REVERSE);
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
    initInputWin();
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

void BoardWin::initInputWin() {
    unsigned width = (xMax*0.5);
    inputWin = newwin(3, width, (unsigned)yMax*0.3, (unsigned)xMax*0.24);
    refresh();
}

void BoardWin::drawInputBox(string title) {
    werase(inputWin);
    wborder(inputWin, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
    wrefresh(inputWin);
    /* getting box values */
    unsigned boxWidth, boxHeight;
    getmaxyx(inputWin, boxHeight, boxWidth);

    /* printing box "name" */
    wmove(inputWin, 0, (unsigned)boxWidth/2 - title.length());
    wattron(inputWin, A_REVERSE);
    wprintw(inputWin, title.c_str());
    wattroff(inputWin, A_REVERSE);
}

string BoardWin::getData(string title) {
    string data;
    drawInputBox(title);
    unsigned boxWidth, boxHeight;
    getmaxyx(inputWin, boxHeight, boxWidth);

    /* the user start typing here */
    int c(0), x(1), y(1);
    string  prov("");
    wmove(inputWin, 1, x++);
    while((c = wgetch(inputWin)) != 10) {
        getyx(inputWin, y, x);
        if(x >= boxWidth - 2 && c != 127) {
            werase(inputWin);
            drawInputBox(title);
            wmove(inputWin, 1, 1);
            wprintw(inputWin, data.c_str());
        } 
        else {
            if(c == 127) {
                if(data.length() > 0) {
                    /* erase backspace and the last char */
                   // data.pop_back();
                    data.pop_back();
                    werase(inputWin);
                    drawInputBox(title);
                    wmove(inputWin, 1, 1);
                    wprintw(inputWin, data.c_str());
                }
            }
            else {
                /* append char to string */
                data += c;
                werase(inputWin);
                drawInputBox(title);
                wmove(inputWin, 1, 1);
                wprintw(inputWin, data.c_str());
            }
        }
    }
    return data;
}

void BoardWin::addTask() {
    string provContent, provTag;
    provContent = getData("content: ");
    provTag = getData("Tag: ");
    B.getList(selectedList).addTask(provContent, provTag);
}

void BoardWin::renameTask() {
    string provContent;
    provContent = getData("content: ");
    B.getList(selectedList).getTask(selectedListTask).setContent(provContent);
}

void BoardWin::addList() {
    string provName;
    provName = getData("name: ");
    B.createList(provName);  
    selectedList = B.getNumLists() - 1;
}

void BoardWin::renameList() {
    string provName;
    provName = getData("name: ");
    B.getList(selectedList).setName(provName);
}

void BoardWin::initInfoWin() {
    unsigned infoWinHeight = (yMax*0.25);
    infoWin = newwin(infoWinHeight, xMax - 3, yMax - infoWinHeight, 1); 
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
    if(!listOrDones && B.getDones().getSize() > 0) {
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
    else if(B.getList(selectedList).getSize() > 0) {
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

void BoardWin::printListWin() {
    if(B.getNumLists() > 0) {
        listWin.print(selectedListTask, B.getList(selectedList), listOrDones); 
    }
    else {
        listWin.printEmpty();
    }
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

        case 97: //a
            addTask();
            break;

        case 65: //A
            addList();
            break;

        case 100: //d
            if(listOrDones && B.getList(selectedList).getSize() > 0) { 
                B.getList(selectedList).removeTask(selectedListTask);
                if(selectedListTask > 0) selectedListTask--;
            }
            else if(B.getDones().getSize() > 0) {
                B.getDones().removeTask(selectedDoneTask);
                if(selectedDoneTask > 0) selectedDoneTask--;
            }
            break;

        case 68: //D
            if(listOrDones && B.getNumLists() > 0) {
                B.removeList(selectedList);
                if(selectedList > 0) selectedList--;
            }
            break;

        case 114: //r
            if(listOrDones && B.getNumLists() > 0 && B.getList(selectedList).getSize() > 0) {
                renameTask();
            }
            break;

        case 82: //R
            if(listOrDones && B.getNumLists() > 0) {
                renameList();
            }
            break;

        case 10: // Enter
            if(listOrDones && B.getList(selectedList).getSize() > 0) {
                B.finishTask(selectedList, selectedListTask);
                if(selectedListTask > 0) selectedListTask--;
            }
            break;

        default:
            break;
    }
    doneWin.erase();
    printDoneWin();
    listWin.erase();
    printListWin();
    werase(infoWin);
    printInfoWin();

    return c;
}
