#include "luTask.h"
#include <string>
#include <iostream>

using namespace std;

void Task::save(ostream& X) const {
    X << "\"" << this->content << "\";";
    X << "#" << this->tag << ";";
    X << this->initDate << ";";
    if(this->done) X << "finished;" << this->finishDate << ";";
    else X << "pending;";
}

bool Task::read(istream& X) {
    string prov;
    getline(X, prov, '"'); // discarting first quotation marks
    if(prov != "") return false;
    getline(X, prov, '"'); // reading content
    this->content = prov;

    getline(X, prov, '#');
    if(prov != ";") return false;
    getline(X, prov, ';'); // reading tag
    this->tag = prov;

    Date Dprov;
    if(!Dprov.read(X)) return false; // reading init date
    this->initDate = Dprov;

    getline(X, prov, ';'); // reading done
    if(prov == "pending") {
        this->done = false;
        return true;
    }
    if(prov == "finished") {
        this->done = true;
        if(!Dprov.read(X)) return false;    
        this->finishDate = Dprov;
        return true;    
    }
    return false;
}

void Task::typeTask() {
    cerr << "Type the task content: ";
    getline(cin, this->content);
    cerr << "Type the tag: ";
    getline(cin, this->tag);
    this->initDate.setCurrentDate();
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

void TaskList::addTask() {
    Task prov;
    this->tasks.push_back(prov);
    this->tasks.back().typeTask();
}

void TaskList::save(ostream& X) const {
    X << "@media@";
    for(unsigned i=0; i<tasks.size(); i++) {
        X << tasks[i];
    }
    X << "@";
}

bool TaskList::read(istream& X) {
    //
    return true;
}

void TaskList::typeList() {
    cerr << "Say how many lists you want add: ";
    unsigned provint;
    cin >> provint;
    if(provint != 0) {
        Task prov;
        for(unsigned i=0; i<provint; i++) {
            tasks.push_back(prov);
            cout << "Task " << i + 1 << ": ";
            cin >> tasks.back();
        }
    }
}

void TaskList::removeTask() {
    cerr << "Type the idx of the task to remove: ";
    unsigned idx;
    cin >> idx;
    cin.ignore();
    removeTask(idx);
}

void Board::createList() {
    cerr << "Type the name of the list: ";
    string name;
    getline(cin, name);
    this->lists.push_back(TaskList(name)); 
}

void Board::removeList() {
    cerr << "Type the idx of the list to remove: ";
    unsigned idx;
    cin >> idx;
    cin.ignore();
    removeList(idx);
}

void Board::showLists() const {
    cout << "@@ BOARD @@\n\t";
    if(getNumLists() == 0) {
        cerr << "Empty board!\n\t";
        return;
    } 
    else {
        for(unsigned i=0; i<this->lists.size() - 1; i++){
            cout << "list " << (i + 1) << ":\n\t\t";
            this->lists[i].printList();
            cout << endl;
        }
        cout << "list " << this->lists.size() - 1 << ":\n\t\t";
        this->lists[this->lists.size() - 1].printList();
    }
}
