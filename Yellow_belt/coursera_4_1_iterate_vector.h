#include <vector>
#include <algorithm>

void PrintVectorPart(const vector<int>& numbers){
    vector<int>::iterator it = find_if(begin(numbers), end(numbers),
                    [](int& num){
                    return (num < 0);
                    })
    while(it != end(numbers)){
        ++it;
        cout << *it << " ";
    }
}

int main(){
    vector<int> nums = {1, 2, 3, 4, 5, -2, 3, 3, 4, 6};
    PrintVectorPart(nums);
}
