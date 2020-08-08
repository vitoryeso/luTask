#ifndef LU_TASK_H
#define LU_TASK_H

/*
 * ok vamos criar um app de gerenciamento de tasks
 * vamos poder criar listas e dentro dos quadros terao tasks
 * o maior elemento visivel sao os quadros que contem as listas
 * terao poucos quadros
 *
 */

#include <string>
#include <vector>
#include <iostream>
#include <luUtils.h>
using namespace std;

class Task {
private:
    string content;
	string tag;
    Date initDate;
    Date finishDate;
    bool done;
public: 
    // dont use
	Task(): content(""), tag(""), done(false) {}
    // use this
	Task(const string content, const string tag) {
		this->content=content;
		this->tag=tag;
		this->initDate.setCurrentDate();
		this->done=false;
	}
	inline string getContent() const {return this->content;}
	inline string getTag() const {return this->tag;}
	inline Date getInitDate() const {return this->initDate;}
	inline Date getFinishDate() const {return this->finishDate;}
    inline bool isDone() const {return this->done;}
	inline void setContent(const string content) {this->content=content;}
	inline void setTag(const string tag) {this->tag=tag;}

	inline void finish() {finishDate.setCurrentDate(); done=true;}

    //file options
    void save(ostream& X) const;
    bool read(istream& X);

    //user input options
    void printTask() const ;
    void typeTask();
};

ostream& operator<<(ostream& X, const Task T);
istream& operator>>(istream& X, Task& T);

// this class get all tasks pending and finished. the idea is separate pending and finished using sort
class TaskList {
private:
	string name;
	vector<Task> tasks;
public:
	TaskList(): name("") {};
    TaskList(const string name) {this->name=name;}

    inline string getName() const {return this->name;}
    inline Task& getTask(const unsigned i) {return this->tasks.at(i);} // returning by reference

	inline void addTask(const string content, const string tag) {tasks.push_back(Task(content, tag));}
    void addTask();

    inline void removeTask(const unsigned i) {tasks.erase(tasks.begin() + i);}
    void removeTask();

    void finishSomeTask();
	void finishTask(const unsigned i);
    
    void sortByDone();
    //unsigned getLastDone() const;
    //void sortByTag();
    //void sortByInitDate();    

    // file options
    void save(ostream& X) const;
    bool read(istream& X);

    // user input options
    void printList(bool selected=false) const;
    void typeList();
};

inline ostream& operator<<(ostream& X, const TaskList TL) {TL.save(X); return X;}
inline istream& operator>>(istream& X, TaskList& TL) {if(&X == &cin) TL.typeList(); else if(!TL.read(X)) cerr << "Invalid File!\n"; return X;}


class Board {
private:
    vector<TaskList> lists;
public:
    
    inline unsigned getNumLists() {return lists.size();}
    inline void createList(const string name) {this->lists.push_back(TaskList(name));}
    void createList();

    inline void removeList(const unsigned i) {this->lists.erase(lists.begin() + i);}
    void removeList();

    inline TaskList& getList(const unsigned i) {return this->lists.at(i);} // returning by reference
    void showLists(const unsigned selectedList) const;

    // file utils functions
    void save(ostream& X) const;
    bool read(istream& X);

    // write and load from filepath
    void write(const string filepath) const;
    bool load(const string filepath);
};




#endif
