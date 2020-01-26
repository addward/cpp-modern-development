#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

void TestConstruction() {
  SimpleVector<int> empty;
  ASSERT_EQUAL(empty.Size(), 0u);
  ASSERT_EQUAL(empty.Capacity(), 0u);
  ASSERT(empty.begin() == empty.end());

  SimpleVector<string> five_strings(5);
  ASSERT_EQUAL(five_strings.Size(), 5u);
  ASSERT(five_strings.Size() <= five_strings.Capacity());
  for (auto& item : five_strings) {
    ASSERT(item.empty());
  }
  five_strings[2] = "Hello";
  ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
  SimpleVector<int> v;
  for (int i = 10; i >= 9; --i) {
    v.PushBack(i);
    //cout << v.Size() << ", " << v.Capacity() << endl;
    ASSERT(v.Size() <= v.Capacity());
  }
  /*for (auto i = begin(v); i != end(v); ++i){
    cout << *i << " ";
  }
  cout << endl;*/
  sort(begin(v), end(v));
  /*for (auto i = begin(v); i != end(v); ++i){
    cout << *i << " ";
  }
  cout << endl;*/

  const vector<int> expected = {/*1, 2, 3, 4, 5, 6, 7, 8,*/ 9, 10};
  ASSERT_EQUAL(v.Size(), expected.size());
  ASSERT(equal(begin(v), end(v), begin(expected)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestPushBack);
  /*SimpleVector<string> sv;
  string a;
  cout << "Size: " << sv.Size() << ", Capacity: " << sv.Capacity() << endl;
  while (cin >> a){
    sv.PushBack(a);
    cout << "Size: " << sv.Size() << ", Capacity: " << sv.Capacity() << endl;
  }
  return 0;*/
}
