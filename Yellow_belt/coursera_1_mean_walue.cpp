#include <iostream>
#include <vector>

using namespace std;

int main(){
    unsigned long n;
    cin >> n;
    vector<int> temps(n);

    long mean = 0;
    for (unsigned long k = 0; k < n; ++k){
        cin >> temps[k];
        mean += temps[k];
    }
    mean /= n;
    // Check the days with temperature higher than mean;
    vector<unsigned int> days;
    for (size_t i = 0; i < temps.size(); i++){
        if (temps[i] > mean) {
            days.push_back(i);
        }
    }
    // Print number of days and their index in console
    cout << days.size() << endl;
    for (auto idx: days){
        cout << idx << " ";
    }
}
