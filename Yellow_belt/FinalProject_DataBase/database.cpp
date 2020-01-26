#include "database.h"
#include "algorithm"

void Database::Add(const Date& date, const string& event) {
    /*list<string>& events = database_[date];
    auto it = find(begin(events), end(events), event);
    if (it == end(events)){
        database_[date].push_back(event);
    }*/
    database_[date].addEvent(event);
}

void Database::Print(ostream& os) const {
    for (auto p: database_){
        const list<string>& events = p.second.getEvents();
        for (auto evs: events){
            os << p.first << " " << evs << endl;
        }
    }
}

string Database::Last(const Date& date){
    auto it = database_.lower_bound(date);
    ostringstream ss;
    if (it->first == date){
        ss << date << " " << *(--end((it->second).getEvents()));
    } else if (it != begin(database_)){
        --it;
        ss << it->first << " " << *(--end((it->second).getEvents()));
    } else {
        return "No entries";
    }
    return ss.str();
}

void EventsContainer::addEvent(const string& event){
    if (iterators_.count(event) > 0){
        return;
    } else {
        events_.push_back(event);
        iterators_[event] = --end(events_);
    }
}

bool EventsContainer::removeEvent(const string& event){
    if (iterators_.count(event) == 0){
        return false;
    } else {
        auto it = iterators_[event];
        events_.erase(it);
        iterators_.erase(event);
        return true;
    }
}

list<string> EventsContainer::getEvents() const {
    return events_;
}
