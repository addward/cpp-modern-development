#include <list>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
int size;
cin >> size;
list<int> sportsmen;
vector<list<int>::iterator> iterators(100000, sportsmen.end());

for (int i = 0; i < size; ++i){
    int player, position;
    cin >> player >> position;
    auto it = iterators[position];
    auto itInserted = sportsmen.insert(it, player);
    iterators[player] = itInserted;
}
for (auto it = begin(sportsmen); it != end(sportsmen); ++it) {
    cout << *it << " ";
}
}
