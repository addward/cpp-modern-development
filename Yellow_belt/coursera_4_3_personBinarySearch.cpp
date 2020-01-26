#include <iostream>
#include <map>
#include <string>

using namespace std;

class Person {
public:
  void ChangeFirstName(int year, const string& first_name_str) {
    first_name[year] = first_name_str;
  }
  void ChangeLastName(int year, const string& last_name_str) {
    second_name[year] = last_name_str;
  }
  string GetFullName(int year) {
    string firstName = findName(first_name, year);
    string secondName = findName(second_name, year);

    if (firstName.empty() && secondName.empty()){
        return "Incognito";
    } else if (firstName.empty()){
        return secondName + " with unknown first name";
    } else if (secondName.empty()){
        return firstName + " with unknown last name";
    } else {
        return firstName + " " + secondName;

    }
  }
private:
  map<int, string> first_name, second_name;
  string findName(map<int, string>& m, int year){
    auto notLowerIt = m.upper_bound(year);
    string res;
    if (notLowerIt != m.begin()){
        res = (--notLowerIt)->second;
    }
    return res;
  }
};

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  return 0;
}
