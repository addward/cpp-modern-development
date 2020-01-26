#pragma once

#include <iostream>
#include <sstream>

using namespace std;

class Date{
public:
    Date(int day, int month, int year);
    string getDate() const;
    int getYear() const ;
    int getMonth() const ;
    int getDay() const ;
private:
    const int day_, month_, year_;
};

Date ParseDate(istream& is);

ostream& operator<< (ostream& os, const Date& d);

bool operator< (const Date& lhs, const Date& rhs);

bool operator== (const Date& lhs, const Date& rhs);

bool operator> (const Date& lhs, const Date& rhs);

bool operator>= (const Date& lhs, const Date& rhs);

bool operator<= (const Date& lhs, const Date& rhs);

bool operator!= (const Date& lhs, const Date& rhs);
