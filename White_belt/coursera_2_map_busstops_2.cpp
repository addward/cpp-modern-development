#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int num;
    cin >> num;
    map<vector<string>, int> bus_route;

    for(int i = 0; i < num; ++i){
        int num_stops;
        cin >> num_stops;
        int number = bus_route.size() + 1;
        vector<string> stops;
        for (int n = 0; n < num_stops; ++n){
            string stop;
            cin >> stop;
            stops.push_back(stop);
        }
        if (bus_route.count(stops) == 0){
                bus_route[stops] = number;
                cout << "New bus " << number << endl;
        }
        else cout << "Already exists for " << bus_route[stops] << endl;
    }

    return 0;
}
