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
    cout << "AAAAAAAAAAAAAAAAAAAAA" << endl;

    string prov2;
    getline(X, prov2, '"');
    cout << prov2 << endl;


    return true;
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

void TaskList::printList() const {
    if(this->tasks.size() == 0) {
        cerr << "Empty list!\n";
        return;
    }
    else {
        for(unsigned i=0; i<this->tasks.size(); i++) {
            cout << (i + 1) << ": ";
            this->tasks[i].printTask();
            cout << endl;    
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
