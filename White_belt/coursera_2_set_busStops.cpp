#include <map>
#include <set>
#include <iostream>

using namespace std;

int main (){
    int num;
    cin >> num;
    map<set<string>, int> routes;
    for (int i = 0; i < num; ++i){
        int nstops;
        cin >> nstops;

        set<string> stops;
        string stop;

        for (int n = 0; n < nstops; ++n){
                cin >> stop;
                stops.insert(stop);
        }
        int mapSize = routes.size() + 1;

        if (routes.count(stops) == 1)
            cout << "Already exists for " << routes[stops] << endl;
        else {
            cout << "New bus " << mapSize << endl;
            routes[stops] = mapSize;
        }

    }
    return 0;
}
