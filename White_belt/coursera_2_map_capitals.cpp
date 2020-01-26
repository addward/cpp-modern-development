#include <map>
#include <iostream>

using namespace std;

int main(){
int num;
cin >> num;
map <string, string> capitals;

for (int i = 0; i < num; i++){
    string command;
    cin >> command;
    if (command == "CHANGE_CAPITAL"){
        string country, capital;
        cin >> country >> capital;
        if (capitals.count(country) == 0){
            cout << "Introduce new country " << country << " with capital " << capital << endl;
            capitals[country] = capital;
            continue;
        } else {
            if(capitals[country] == capital){
                cout << "Country " << country << " hasn't changed its capital" << endl;
            } else {
                string old_capital = capitals[country];
                capitals[country] = capital;
                cout << "Country " << country << " has changed its capital from " << old_capital << " to " << capital << endl;
            }
        }
    } else if (command == "RENAME"){
        string old_country_name, new_country_name;
        cin >> old_country_name >> new_country_name;

        if (capitals.count(old_country_name) == 0 || capitals.count(new_country_name) > 0){
            cout << "Incorrect rename, skip" << endl;
        } else {
            string capital = capitals[old_country_name];
            capitals.erase(old_country_name);
            capitals[new_country_name] = capital;
            cout << "Country " << old_country_name << " with capital " << capital << " has been renamed to " << new_country_name << endl;
        }

    } else if (command == "ABOUT"){
        string country;
        cin >> country;
        if (capitals.count(country) == 0){
            cout << "Country " << country << " doesn't exist" << endl;
        } else {
            cout << "Country " << country << " has capital " << capitals[country] << endl;
        }

    } else if (command == "DUMP"){
        if (capitals.size() == 0){
            cout << "There are no countries in the world" << endl;
        } else {
            for (auto c: capitals){
                cout << c.first << "/" << c.second << endl;
            }
        }
    }
}

return 0;
}
