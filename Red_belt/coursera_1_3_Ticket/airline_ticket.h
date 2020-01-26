#pragma once

#include <string>
#include <vector>

using namespace std;

struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};

void SortTickets(vector<AirlineTicket>& tixs);
bool operator< (const Date& lhs, const Date& rhs);
bool operator< (const Time& lhs, const Time& rhs);
ostream& operator<< (ostream& os, const Time& t);
ostream& operator<< (ostream& os, const Date& d);
bool operator!= (const Date& lhs, const Date& rhs);
bool operator == (const Date& lhs, const Date rhs);
