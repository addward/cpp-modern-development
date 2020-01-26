#include <map>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void printBuses(const vector<string>& b, string bus){
    if (b.empty() || ( b.size() == 1 && find(b.begin(), b.end(), bus) != b.end())){
        cout << "no interchange";
    } else {
        for(auto e: b){
            if (bus == "" || bus != e){
                cout << e << " ";
            }
        }
    }
    cout << endl;
}

int main(){
    int q;
    cin >> q;
    map <string, vector<string>> buses;
    map <string, vector<string>> stops;

    for (int i = 0; i < q; ++i){
        string command;
        cin >> command;

        if (command == "NEW_BUS"){
            string busName, stationName;
            int m;
            cin >> busName >> m;
            for (int n = 0; n < m; ++n){
                cin >> stationName;
                buses[busName].push_back(stationName);
                stops[stationName].push_back(busName);
            }
        } else if (command == "BUSES_FOR_STOP"){
            string stop;
            cin >> stop;
            if (stops.count(stop) == 0){
                cout << "No stop" << endl;
            } else {
                printBuses(stops[stop], "");
            }
        } else if (command == "STOPS_FOR_BUS"){
            string bus;
            cin >> bus;
            if (buses.count(bus) == 0){
                cout << "No bus" << endl;
            } else {
                for (auto s: buses[bus]){
                    cout << "Stop " << s << ": ";
                    printBuses(stops[s], bus);
                }
            }
        } else if (command == "ALL_BUSES"){
            if (buses.empty()){
                cout << "No buses" << endl;
            } else {
                for (auto b: buses){
                    cout << "Bus " << b.first << ": ";
                    for (auto stop: b.second){
                        cout << stop << " ";
                    }
                    cout << endl;
                }
            }
        }
    }
    return 0;
}
