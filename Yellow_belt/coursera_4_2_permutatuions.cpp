#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

int main(){
    int size;
    cin >> size;
    vector<int> array1(size);
    iota(begin(array1), end(array1), 1);
    do{
        for_each(rbegin(array1), rend(array1), [](int num){
                    cout << num << " ";
                 });
        cout << endl;
    }while (prev_permutation(rbegin(array1), rend(array1)));
}
