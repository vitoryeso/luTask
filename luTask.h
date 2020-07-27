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
#include "luUtils.h"

using namespace std;

class Task {
private:
    string content;
    Date initDate;
    Date finishDate;
    bool done;
public: 
		Task(): content(""), initDate.setCurrentDate(), done=false {}
		Task(const string content) {
				this->content=content;
				this->initDate.setCurrentDate();
				this->done=false;
		}
		inline string getContent() const {return this->content;}
		inline Date getInitDate() const {return this->initDate;}
		inline Date getFinishDate() const {return this->finishDate;}
		inline void setContent(const string content) {this->content=content;}

		inline void finish() {finishDate.setCurrentDate(); done=true;}
};

class List {
private:
		string name;
		Task *tasksToDo;
		Task *tasksDone;
		unsigned numTasksToDo;
		unsigned numTasksDone;
public:
		
		
}

class Quadro {
private:

};




#endif
