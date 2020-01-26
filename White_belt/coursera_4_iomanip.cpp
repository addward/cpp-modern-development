#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main(){
    fstream file("input.txt");
    double num;
    cout << fixed << setprecision(3);
    while(file.good()){
        file >> num;
        cout << num << endl;
    }
}
