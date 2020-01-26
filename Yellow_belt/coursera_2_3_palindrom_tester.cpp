#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

void test_predefined(){
    Assert(IsPalindrom("asasa"),"asasa");
    Assert(IsPalindrom(""),"empty");
    Assert(IsPalindrom("a"),"a");
    Assert(IsPalindrom("asa  asa"),"asa asa");
    Assert(!IsPalindrom("k opok"),"k opok");
    Assert(!IsPalindrom("pips"),"pips");
    Assert(IsPalindrom("VeryyreV"),"VeryyreV");
    Assert(!IsPalindrom("Veryrev"),"Veryrev");
    Assert(IsPalindrom("TheLongnoLehT"),"TheLongnoLehT");
    Assert(!IsPalindrom("abskekabkeksba"),"abskekabkeksba");
    Assert(!IsPalindrom("abs asba"),"abs asba");
    Assert(IsPalindrom("hellolleh"),"hellolleh");
    Assert(!IsPalindrom(" ellolleh")," ellolleh");
    Assert(!IsPalindrom("-ellolleh"),"-ellolleh");
    Assert(!IsPalindrom("?ellolleh"),"?ellolleh");
    Assert(!IsPalindrom(" ellolle")," ellolle");
    Assert(IsPalindrom("123321"),"123321");
    Assert(IsPalindrom("12321"),"12321");
}
int main() {
  TestRunner runner;
  runner.RunTest(test_predefined, "Predefined test");
  return 0;
}
