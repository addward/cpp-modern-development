#include "sum_reverse_sort.h"
#include <algorithm>

int Sum(int x, int y){
    return x + y;
}

string Reverse(string s){
    string reversed(s.rbegin(), s.rend());
    return reversed;
}

void Sort(vector<int>& nums){
    return sort(nums.begin(), nums.end());
}
