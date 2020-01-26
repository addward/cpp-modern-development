#include <iostream>
#include <iomanip>
#include <map>
#include <set>
// Реализуйте функции и методы классов и при необходимости добавьте свои

using namespace std;

class Date {
public:
  Date(){
      this->year = 0;
      this->month = 0;
      this->day = 0;
  }
  Date(string date){
      stringstream ss(date);
      if(!(ss >> year) && ss.peek() != '-'){
        throw runtime_error("Wrong date format: " + date);
      }
      ss.ignore();
      if(!(ss >> month) && ss.peek() != '-'){
        throw runtime_error("Wrong date format: " + date);
      }
      ss.ignore();
      if(!(ss >> day) && ss.peek() != '-'){
        throw runtime_error("Wrong date format: " + date);
      }
      if (ss.peek() != -1){
        throw runtime_error("Wrong date format: " + date);
      }
      if (month < 1 || month > 12)
        throw runtime_error("Month value is invalid: " + to_string(month));
      if (day < 1 || day > 31)
        throw runtime_error("Day value is invalid: " + to_string(day));
  }
  int GetYear() const{
    return year;
  }
  int GetMonth() const{
    return month;
  }
  int GetDay() const{
    return day;
  }
private:
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs){
    if (lhs.GetYear() < rhs.GetYear()){
        return true;
    } else if (lhs.GetYear() == rhs.GetYear()){
        if (lhs.GetMonth() < rhs.GetMonth()){
            return true;
        } else if (lhs.GetMonth() == rhs.GetMonth()){
            if (lhs.GetDay() < rhs.GetDay()){
                return true;
            } else return false;
        } else return false;
    } else {
        return false;
    }
}

ostream& operator<<(ostream & stream, const Date& date){
    cout << setfill('0');
    cout << setw(4) << date.GetYear() << '-' << setw(2) << date.GetMonth() << '-' << setw(2) << date.GetDay();
    return stream;
}

class Database {
private:
  map <Date, set<string>> db;

public:
  void AddEvent(const Date& date, const string& event){
    if (event != "") db[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event){
    set<string> el;
    try {
        el = db.at(date);
    } catch (out_of_range e){
        return false;
    }
    set<string>::iterator it = db[date].find(event);
    if (it != db[date].end()){
        db[date].erase(it);
        return true;
    } else return false;
  }

  int  DeleteDate(const Date& date){
    set<string> el;
    try {
        el = db.at(date);
    } catch (out_of_range e){
        return 0;
    }
    db.erase(date);
    return el.size();
  }

  set<string> Find(const Date& date) const{
    set<string> el;
    try {
        el = db.at(date);
    } catch (out_of_range e){
        return set<string>{};
    }
    return el;
  }

  void Print() const{
    for (auto it = db.begin(); it != db.end(); it++){
        for (auto it1 = (it->second).begin(); it1 != (it->second).end(); it1++){
            cout << it->first << " " << *it1;
            if (it1 != --((it->second)).end()) cout << endl;
        }
        cout << endl;
    }
  }
};

int main() {
  Database db;

  string command;
  while (getline(cin, command)) {
    stringstream ss(command);
    string name;
    ss >> name;
    if (name == "Add" || name == "Del" || name == "Find"){

        string dateString;
        ss >> dateString;
        Date date;
        try{
            date = Date(dateString);
        } catch (runtime_error e){
            cout << e.what() << endl;
            return(0);
        }
        if (name == "Add"){

            string eventName;
            ss >> eventName;
            db.AddEvent(date, eventName);

        } else if (name == "Find"){

            set<string> evs = db.Find(date);
            for (const string& s: evs){
                cout << s << endl;
            }

        } else if (name == "Del") {

            string event;
            if (ss >> event){

                if (db.DeleteEvent(date, event)){

                    cout << "Deleted successfully" << endl;

                } else {

                    cout << "Event not found" << endl;

                }

            } else {

                cout << "Deleted " + to_string(db.DeleteDate(date)) + " events" << endl;

            }
        }
    } else if (name == "Print"){
        db.Print();
    } else if (name == ""){
    } else {
        cout << "Unknown command: " << name << endl;
        return(1);
    }
  }

  return 0;
}
