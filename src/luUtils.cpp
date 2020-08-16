#include "luUtils.h"
#include <iostream>
#include <string>

using namespace std;

bool charCheck(istream& X, const char c) {
    char prov;
    X.get(prov);
    return (c != prov) ? false : true;
}

Date::Date(const unsigned day, const unsigned month, const unsigned year) {
    if(check(day, month, year)) {
        this->day = day;
        this->month = month;
        this->year = year;
    }    
    else {
       	load(1, 1, 1); 
    }
}

string Date::getStr() const {
    string prov("");
    if(this->day < 10) prov += "0" + to_string(this->day) + "/";
    else prov += to_string(this->day) + "/";
    if(this->month < 10) prov += "0" + to_string(this->month) + "/";
    else prov += to_string(this->month) + "/";
    prov += to_string(this->year);
    return prov;
}

void Date::save(ostream& X) const { 
    X << this->day << "-";
    X << this->month << "-";
    X << this->year;
}

bool Date::read(istream& X) {
   	unsigned day, month, year;
    X >> day;
    X.ignore();
    if(!checkDay(day)) return false;
    string prov;
    X >> month;
    X.ignore();
    if(!checkMonth(month)) return false;
    X >> year;
    X.ignore();
    if(!checkYear(year)) return false;
    load(day, month, year);
    return true;
}

void Date::type() {
		unsigned day, month, year;
		cerr << "digite o dia: ";
		cin >> day;
		if(!checkDay(day)) {
				cerr << "dia incorreto.\n";
				return;
		}
		cerr << "digite o mes: ";
		cin >> month;
		if(!checkMonth(month)) {
				cerr << "mes incorreto.\n";
				return;
		}
		cerr << "digite o ano: ";
		cin >> year;
		if(!checkYear(year)) {
				cerr << "year incorreto.\n";
				return;
		}
		load(day, month, year);
}

void Date::setCurrentDate() {
		time_t prov = time(0);
		tm *prov2 = localtime(&prov);
		load(prov2->tm_mday, prov2->tm_mon + 1, prov2->tm_year + 1900);
}
