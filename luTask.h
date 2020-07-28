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
	inline void setContent(const string content) {this->content=content;}
	inline void setTag(const string tag) {this->tag=tag;}

	inline void finish() {finishDate.setCurrentDate(); done=true;}
};

// this class get all tasks pending and finished. the idea is separate pending and finished using sort
class TaskList {
private:
	string name;
	vector<Task> tasks;
public:
	TaskList(): name("") {};

    inline string getName() const {return this->name;}
    inline Task getTask(const unsigned i) const {return this->tasks.at(i);}

	inline void addTask(const Task& T) {tasks.push_back(T);}
	inline void finishTask(const unsigned i) {tasks.at(i).finish();}
    
    void sortByDone();
    unsigned getLastDone() const;
    void sortByTag();
    void sortByInitDate();    
};

class Quadro {
private:

};




#endif
