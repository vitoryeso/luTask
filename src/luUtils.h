#ifndef LU_UTILS_H
#define LU_UTILS_H

/*
 * o arquivo contem:
 *  Data - classe
*/

#include <string>
#include <iostream>

using namespace std;

// check next char from stream and consume it. return a bool representing if this char match with a parameted char
bool charCheck(istream& X, const char c);
// classe Data com algumas utilidades como checagem de entradas e operadores de entrada e saída.
class Date {
private:
    unsigned day;
    unsigned month;
    unsigned year;
		inline void load(const unsigned day, const unsigned month, const unsigned year) {this->day=day; this->month=month; this->year=year;}
public:
    Date(): day(1), month(1), year(1) {}
    Date(const unsigned day, const unsigned month, const unsigned year);

    inline unsigned getDay() const {return this->day;}
    inline unsigned getMonth() const {return this->month;}
    inline unsigned getYear() const {return this->year;}
    inline void setDay(const unsigned day) {if(checkDay(day)) this->day = day;}
    inline void setMonth(const unsigned month) {if(checkMonth(month)) this->month = month;}
    inline void setYear(const unsigned year) {if(checkYear(year)) this->year = year;}
		
		void setCurrentDate();

    inline bool checkDay(const unsigned day) const {return day > 0 && day < 32 ? true : false;}
    inline bool checkMonth(const unsigned month) const {return month > 0 && month < 13 ? true: false;}
    inline bool checkYear(const unsigned year) const {return year > 0 ? true : false;}
    inline bool check(const unsigned day, const unsigned month, const unsigned year) const {if(checkDay(day) && checkMonth(month) && checkYear(year)) return true; else return false;}

    string getStr() const;

    // usando arquivos
    void save(ostream& X) const;
    bool read(istream& X);

    // usando entrada e saida do usuario
    void type();
    inline void print() const {save(cout);}; 

};

inline ostream& operator<<(ostream& X, const Date& D) {D.save(X); return X;} 
inline istream& operator>>(istream& X, Date& D) {if(&X == &cin) D.type(); else D.read(X); return X;}

#endif
