#include <iostream>
#include <vector>

using namespace std;

struct student{
 string name, surname;
 int day, month, year;
};

int main(){
    int num;
    cin >> num;
    vector<student> students(num);
    //cout << students.size();
    for(int i = 0; i < num; ++i){
        string name, surname;
        int day, month, year;
        cin >> name >> surname;
        cin >> day >> month >> year;
        students[i] = student{name, surname, day, month, year};
    }

    cin >> num;

    for (int i = 0; i < num; ++i){
        string comand;
        int code;

        cin >> comand >> code;
        --code;

        if ((comand != "name" && comand != "date") || code < 0 || code > students.size() - 1 || students.size() == 0) {
                cout << "bad request";
        }else if (comand == "name") {
            cout << students[code].name << " " << students[code].surname;
        } else {
            cout << students[code].day << "." << students[code].month << "." << students[code].year;
        }
        if (i != num - 1)
            cout << endl;
    }
}
