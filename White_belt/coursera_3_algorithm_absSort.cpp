#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void print(const vector<int> & v){
    for (auto & e:v){
        cout << e << " ";
    }
    cout << endl;
}

int main(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i){
        int num;
        cin >> num;
        nums[i] = num;
    }
    sort(begin(nums), end(nums), [](int i, int k){return abs(i) < abs(k);});
    print(nums);
    return 0;
}
