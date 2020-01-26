#pragma once

#include <ostream>
#include <list>
#include <vector>
#include <map>
#include "date.h"

using namespace std;

struct EventsContainer{
public:
    void addEvent    (const string& event);
    bool removeEvent (const string& event);
    list<string> getEvents() const;
private:
    list<string> events_;
    map<string, list<string>::iterator> iterators_;
};

class Database{
public:
    void Add(const Date& date, const string& event);

    void Print(ostream& os) const;

    string Last(const Date& date);

    template <class Func>
    int RemoveIf(Func func);

    template <class Func>
    vector<string> FindIf(Func func) const ;

    string Last(const Date& date) const ;
private:
    map<Date, EventsContainer> database_;
};

void TestDatabase();

template <class Func>
int Database::RemoveIf(Func func){
    int deletedCounter = 0;

    for (auto itMap = begin(database_); itMap != end(database_);){
        auto listEvs = (itMap->second).getEvents();
        auto date = itMap -> first;
        for (auto it = begin(listEvs); it != end(listEvs); ++it){
            if (func(date, *it)){
                ++deletedCounter;
                (itMap->second).removeEvent(*it);
            }
        }
        if ((itMap->second).getEvents().empty()){
            itMap = database_.erase(itMap);
        } else {
            ++itMap;
        }
    }

    return deletedCounter;
}

template <class Func>
vector<string> Database::FindIf(Func func) const {
    vector<string> results;
    for (auto itMap = begin(database_); itMap != end(database_); ++itMap){
        auto listEvents = (itMap->second).getEvents();
        const auto& date       = itMap -> first;
        for (auto it = begin(listEvents); it != end(listEvents); ++it){
            if(func(date, *it)){
                ostringstream ss;
                ss << date << " " << *it;
                results.push_back(ss.str());
            }
        }
    }
    return results;
}
