#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Person {
public:

    Person(string name, string surName, int year){
           first_name[year] = name;
           second_name[year] = surName;
    }

    void ChangeFirstName(int year, const string& first_name_str) {
        if (year > (*begin(first_name)).first)
            first_name[year] = first_name_str;
    }

    void ChangeLastName(int year, const string& last_name_str) {
        if (year > (*begin(second_name)).first)
            second_name[year] = last_name_str;
    }

    string GetFullName(int year) const{
        vector<string> fn = GetVector(year, first_name), sn = GetVector(year, second_name);
        if (fn.empty() && sn.empty())
            return "No person";
        else if (!fn.empty()) {
            if (!fn.empty()) {
                return fn.back() + " " + sn.back();
            } else {
                return fn.back()+ " with unknown last name";
            }
        } else {
            return sn.back() + " with unknown first name";
        }
    }

    string GetFullNameWithHistory(int year) const{
        string fn = GetNameVector(year, first_name), sn = GetNameVector(year, second_name);
        if (fn.empty() && sn.empty()) return "No person";
        else if (!fn.empty()){
            if (!sn.empty()){
                return fn + " " + sn;
            }
            else return fn + " with unknown last name";
        } else {
            return sn + " with unknown first name";
        }
    }
private:
    map<int, string> first_name, second_name;
    int GetClosestYear(int year, const map<int, string>& m) const{
        if (m.size() == 0) return 0;
        int lyear = (*m.begin()).first;
        for (auto i: m){
            if (i.first <= year && i.first > lyear)
                lyear = i.first;
        }
        if (lyear <= year)
            return lyear;
        else
            return 0;
    }
    vector<string> GetVector(int year, const map<int, string>& m) const{
        vector<string> v;
        for (auto i: m){
            if (i.first <= year && (v.size() == 0 || v.back() != i.second)){
                v.push_back(i.second);
            } else {
                break;
            }
        }
        return v;
    }
    string GetNameVector(int year, const map<int, string>& m) const{
        vector<string> v;
        for (auto i: m){
            if (i.first <= year && (v.size() == 0 || v.back() != i.second)){
                v.push_back(i.second);
            } else {
                break;
            }
        }
        if (v.size() == 0)
            return "";

        string result = v.back();

        if (v.size() > 1)
            result += " (";
        for(int i = v.size() - 2; i >= 0; --i){
            result += v[i];
            if (i != 0)
                result += ", ";
        }

        if (v.size() > 1)
            result += ")";
        return result;
    }
};

int main() {
  Person person("Polina", "Sergeeva", 1960);

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}

