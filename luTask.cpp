#include "luTask.h"
#include <iostream>

using namespace std;

void Task::printTask() const {
    cout << "\"" << this->content << "\";";
    cout << "#" << this->tag << ";";
    cout << this->initDate << ";";
    if(this->done) cout << "finished;" << this->finishDate << ";";
    else cout << "pending;";
}

void Task::typeTask() {
    cerr << "Type the task content: ";
    getline(cin, this->content);
    cerr << "Type the tag: ";
    getline(cin, this->tag);
}

void TaskList::finishTask() {
    cerr << "Type the idx of the task to finish: ";
    unsigned i;
    cin >> i;
    finishTask(i);
    cin.ignore();
}

void TaskList::sortByDone() {
    for(unsigned i=1; i<this->tasks.size(); i++) {
        int j = i - 1;
        while(tasks[i].isDone() < tasks[j].isDone() && j >=0) {
            swap(tasks[j + 1], tasks[j]);
            j--;
        } 
        if(tasks[i].isDone() != tasks[j + 1].isDone()) tasks[j + 1] = tasks[i]; 
    }
}

void TaskList::printList() const {
    for(unsigned i=0; i<this->tasks.size(); i++) {
        cout << (i + 1) << ": ";
        this->tasks[i].printTask();
        cout << endl;    
    }
}

void Board::createList() {
    cerr << "Type the name of the list: ";
    string name;
    getline(cin, name);
    this->lists.push_back(TaskList(name)); 
}
