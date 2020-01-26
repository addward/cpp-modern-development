#include <iostream>
#include <algorithm>

using namespace std;

class ReversibleString{
public:
    ReversibleString(){

    }
    ReversibleString(string str){
        this->str = str;
    }

    string ToString() const{
        return str;
    }

    void Reverse(){
        reverse(begin(str), end(str));
    }

private:
    string str;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;

  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;

  ReversibleString empty1;
  cout << '"' << empty1.ToString() << '"' << endl;

  return 0;
}
