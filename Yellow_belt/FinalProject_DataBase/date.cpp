#include "date.h"
#include <vector>
#include <iomanip>

using namespace std;

Date::Date(int year, int month, int day)
  : day_  (day)
  , month_(month)
  , year_ (year){}

int Date::getYear() const {
  return year_;
}

int Date::getMonth() const {
  return month_;
}

int Date::getDay() const{
  return day_;
}

string Date::getDate() const {
  ostringstream oss;
  oss << setfill('0');
  oss << setw(4) << year_  << "-"
      << setw(2) << month_ << "-"
      << setw(2) << day_;
  return oss.str();
}

Date ParseDate(istream& is){
  string tempString;
  int year, month, day;
  /*get Year*/
  getline(is, tempString, '-');
  year = stoi(tempString);
  /*get Month*/
  getline(is, tempString, '-');
  month = stoi(tempString);
  /*get Day*/
  getline(is, tempString, ' ');
  day = stoi(tempString);
  return {year, month, day};
}

ostream& operator << (ostream& os, const Date& d) {
  return os << d.getDate();
}

bool operator < (const Date& lhs, const Date& rhs) {
  return vector<int>{lhs.getYear(), lhs.getMonth(), lhs.getDay()} <
         vector<int>{rhs.getYear(), rhs.getMonth(), rhs.getDay()};
}

bool operator == (const Date& lhs, const Date& rhs) {
  return vector<int>{lhs.getYear(), lhs.getMonth(), lhs.getDay()} ==
         vector<int>{rhs.getYear(), rhs.getMonth(), rhs.getDay()};
}

bool operator > (const Date& lhs, const Date& rhs) {
  return vector<int>{lhs.getYear(), lhs.getMonth(), lhs.getDay()} >
         vector<int>{rhs.getYear(), rhs.getMonth(), rhs.getDay()};
}

bool operator >= (const Date& lhs, const Date& rhs) {
  return vector<int>{lhs.getYear(), lhs.getMonth(), lhs.getDay()} >=
         vector<int>{rhs.getYear(), rhs.getMonth(), rhs.getDay()};
}

bool operator <= (const Date& lhs, const Date& rhs) {
  return vector<int>{lhs.getYear(), lhs.getMonth(), lhs.getDay()} <=
         vector<int>{rhs.getYear(), rhs.getMonth(), rhs.getDay()};
}

bool operator != (const Date& lhs, const Date& rhs) {
  return !operator==(lhs, rhs);
}
