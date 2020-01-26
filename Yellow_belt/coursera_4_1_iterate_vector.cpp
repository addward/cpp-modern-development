#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

using Iterator = vector<int>::const_iterator;

void PrintVectorPart(const vector<int>& numbers){
    Iterator it = find_if(begin(numbers), end(numbers),
                    [](const int num){
                    return (num < 0);
                    });
    Iterator begIt = begin(numbers);
    while(it != begIt){
        it--;
        cout << *it << " ";
    }
}

int main(){
    vector<int> nums = {1, 2, 3, 4, 5, 2, 3, 3, 4, 6};
    PrintVectorPart(nums);
}

