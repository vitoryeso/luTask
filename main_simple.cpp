#include <iostream>
#include "luTask.h"

using namespace std;

enum cmd{
    EXIT=-1,
    ADD_LIST=1,
    SELECT_LIST,
    ADD_TASK,
    REMOVE_LIST,
    REMOVE_TASK,
    FINISH_TASK
};

void printOptions();
unsigned selectList();

int main(void) {
    Board B;
    bool end=false;
    int cmd;
    unsigned selectedList;
    printOptions();
    while(!end) {
        if(B.getNumLists() > 0) B.showLists();
        cerr << "Type the option: ";
        cin >> cmd;
        cin.ignore();
        switch(cmd) {
            case ADD_LIST:
                B.createList();
                break;
            case SELECT_LIST:
                selectedList = selectList();        
                break;
            case ADD_TASK:
                B.getList(selectedList).addTask();
                break;
            case REMOVE_LIST:
                B.removeList();
                break;
            case REMOVE_TASK:
                B.getList(selectedList).removeTask();
                break;
            case FINISH_TASK:
                B.getList(selectedList).finishTask();
                break;
            case EXIT:
                end=true;
                break;
        }
    }
}

void printOptions() {
    cerr << "### OPTIONS ###\n";
    cerr << "-1: exit\n";
    cerr << "1: add list\n";
    cerr << "2: select list\n";
    cerr << "3: add task\n";
    cerr << "4: remove list\n";
    cerr << "5: remove task\n";
    cerr << "6: finish task\n";
}

unsigned selectList() {
    cerr << "Type the number of the list: ";
    unsigned prov;
    cin >> prov;
    cin.ignore();
    return prov;
}
