#include <map>
#include <iostream>
using namespace std;

template<typename T1, typename T2>
T2& GetRefStrict(map<T1, T2>& m, T1 key){
    if (m.count(key) == 1)
        return (m.at(key));
    else
        throw runtime_error("There's no such element in map");
}
int main(){
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 1);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
}
