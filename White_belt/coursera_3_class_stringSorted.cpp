#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SortedStrings{
private:
    vector<string> strings;
public:
    void AddString(const string& s) {
        strings.push_back(s);
    }
    vector<string> GetSortedStrings() {
        sort(begin(strings), end(strings));
        return strings;
    }
};

int main(){
    SortedStrings strings;

    strings.AddString("first");
    strings.AddString("third");
    strings.AddString("second");
    strings.AddString("second");
    for(auto i : strings.GetSortedStrings()){
        cout << i << " ";
    }

    return 0;
}
