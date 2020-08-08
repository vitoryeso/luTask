#include "luTask.h"
#include <string>
#include <fstream>
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

void Task::printTask() const {
    cout << "\t  ";
    if(!this->done) cout << "\u25A2";
    else cout << "\u25A3";
    cout << " " << this->content << " | " << this->tag;
}

ostream& operator<<(ostream& X, const Task T) {
    if(&X != &cout) {
        T.save(X);
    } 
    else T.printTask();
    return X;
}

istream& operator>>(istream& X, Task& T) {
    if(&X != &cin) {
        if(!T.read(X)) cerr << "Invalid Task File!\n";
    }
    else T.typeTask();
    return X;
}

void TaskList::finishTask(const unsigned i) {
    if(i >= this->tasks.size()) cerr << "Wrong index!\n";
    else this->tasks[i].finish();
}

void TaskList::finishSomeTask() {
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
    X << "@" << this->name << ";";
    X << this->tasks.size() << "@"; 
    for(unsigned i=0; i<tasks.size(); i++) {
        X << this->tasks[i];
    }
    X << "@";
}

bool TaskList::read(istream& X) {
    string prov;
    getline(X, prov, '@');
    if(prov != "") return false;
    getline(X, prov, ';');
    this->name = prov;
    unsigned provLen;
    X >> provLen; /* dont ignore cause we need check if is '@' */
    getline(X, prov, '@');
    if(prov != "") return false;
    Task provTask;
    for(unsigned i=0; i<provLen; i++) {
        tasks.push_back(provTask);
        if(!this->tasks.back().read(X)) return false;
    }
    return true;
}

void TaskList::typeList() {
    cerr << "Type the name of this list of tasks: ";
    string provname;
    getline(cin, provname); /* \n is the default delimiter */
    this->name = provname;
    cerr << "Say how many lists you want add: ";
    unsigned provint;
    cin >> provint;
    cin.ignore();
    if(provint != 0) {
        Task prov;
        for(unsigned i=0; i<provint; i++) {
            tasks.push_back(prov);
            cout << "Task " << i + 1 << ": " << endl;
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

void TaskList::printList(bool selected) const {
    if(!selected) cout << "\tName: " << this->name << endl;
    else {
        cout << "      =>Name: " << this->name << endl;
    }
    if(this->tasks.size() != 0) {
        for(unsigned i=0; i<this->tasks.size(); i++) {
            cout << tasks[i] << endl;
        }
    }
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

void Board::showLists(unsigned selectedList) const {
    cout << "@@ BOARD @@\n";
    if(this->lists.size() == 0) {
        cerr << "Empty board!\n\t";
        return;
    } 
    else {
        for(unsigned i=0; i<this->lists.size(); i++){
            if(i != selectedList) this->lists[i].printList();
            else this->lists[i].printList(true);
            if(i != this->lists.size() - 1) cout << endl;
        }
    }
}

void Board::save(ostream& X) const {
    unsigned size = this->lists.size();
    X << "!";
    if(size != 0) {
        X << size << "!";
        for(unsigned i=0; i<size; i++) {
            X << this->lists[i];
        }
        X << "!";
    }
    else X << size << "!!";
}

bool Board::read(istream& X) {
    string prov;
    if(!charCheck(X, '!')) return false;
    unsigned provLen;
    X >> provLen;
    if(provLen == 0) {
        if(!charCheck(X, '!')) return false;
        if(!charCheck(X, '!')) return false;
        return true;
    }
    else {
        if(!charCheck(X, '!')) return false;
        TaskList provTL;
        for(unsigned i=0; i<provLen; i++) {
            this->lists.push_back(provTL);
            if(!this->lists.back().read(X)) return false;
        } 
        return true;
    }
}

void Board::write(const string filepath) const {
    fstream provfile;
    provfile.open(filepath, fstream::out); 
    this->save(provfile);
    provfile.close();
}

bool Board::load(const string filepath) {
    fstream provfile;
    provfile.open(filepath, fstream::in);    
    if(!this->read(provfile)) return false;
    provfile.close();
    return true; 
}
