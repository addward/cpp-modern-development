#include <set>
#include <iostream>
#include <map>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
  set<string> image;
  for (auto elem: m){
    image.insert(elem.second);
  }
  return image;
}

/*int main(){
    set<string> values = BuildMapValuesSet({
    {1, "odd"},
    {2, "even"},
    {3, "odd"},
    {4, "even"},
    {5, "odd"}
    });

for (const string& value : values) {
  cout << value << endl;
}
    return 0;
}*/
