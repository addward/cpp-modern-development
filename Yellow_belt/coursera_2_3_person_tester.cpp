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
/*
class Person {
public:
  // Вы можете вставлять сюда различные реализации класса,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  void ChangeFirstName(int year, const string& first_name) {
  }
  void ChangeLastName(int year, const string& last_name) {
  }
  string GetFullName(int year) {
  }
};*/

void testSimpleExamples(){
    {
        Person p;
        p.ChangeFirstName(2001, "Ivan");
        p.ChangeLastName(2002, "Divan");
        AssertEqual(p.GetFullName(2002), "Ivan Divan", "Incorrect adding name and lastname");
        AssertEqual(p.GetFullName(2001), "Ivan with unknown last name", "Incorrect added name and empty lastname ");
        AssertEqual(p.GetFullName(2000), "Incognito", "Incognito person");
    }

    {
        Person p;
        p.ChangeFirstName(2001, "Ivan");
        p.ChangeFirstName(2002, "Grisha");
        p.ChangeLastName(2000, "Stepanov");
        p.ChangeLastName(1999, "Ivanov");
        AssertEqual(p.GetFullName(1999), "Ivanov with unknown first name", "Known last name and unknown first name issue");
        AssertEqual(p.GetFullName(2001), "Ivan Stepanov", "Get first name from the past");
        AssertEqual(p.GetFullName(2002), "Grisha Stepanov", "Get current first and last name with existing first name in past");
    }
    {
        Person p;
        AssertEqual(p.GetFullName(2000), "Incognito", "Empty class");

    }
}

int main() {
  TestRunner runner;
  runner.RunTest(testSimpleExamples, "Simple tests");
  return 0;
}
