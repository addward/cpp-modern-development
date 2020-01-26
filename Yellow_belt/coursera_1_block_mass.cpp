#include <iostream>
#include <vector>

using namespace std;

int main(){
    unsigned long long int mass = 0;
    unsigned long int num;
    unsigned int density;
    cin >> num >> density;
    for (unsigned long int i = 0; i < num; ++i){
        unsigned int w, h, d;
        cin >> w >> h >> d;
        mass += static_cast<unsigned long long int>(w) * h * d * density;
    }
    cout << mass;
}
