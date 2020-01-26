#include <string>
#include <vector>
using namespace std;

#define CREATE_VARIABLE2(line, name) name ## line
#define CREATE_VARIABLE(line, name) CREATE_VARIABLE2(line, name)
#define UNIQ_ID CREATE_VARIABLE(__LINE__, variable)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};

}
