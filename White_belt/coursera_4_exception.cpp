#include <iostream>

using namespace std;

void EnsureEqual(const string & left, const string & right){
    if (left != right) {
        throw runtime_error(left + " != " + right);
    } else {
        return;
    }
}

int main(){
    try {
    EnsureEqual("C++ White", "C++ White");
    EnsureEqual("C++ White", "C++ Yellow");
  } catch (exception& e) {
    cout << e.what() << endl;
  }
  return 0;
}
