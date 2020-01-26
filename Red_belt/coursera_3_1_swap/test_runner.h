#pragma once

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T1, class T2>
ostream& operator << (ostream& os, const pair<T1, T2>& p);

template <class T>
ostream& operator << (ostream& os, const vector<T>& s);

template <class T>
ostream& operator << (ostream& os, const set<T>& s);

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m);

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = string{});

void Assert(bool b, const string& hint);


class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name);

  ~TestRunner();

private:
  int fail_count = 0;
};

template <class T1, class T2>
ostream& operator << (ostream& os, const pair<T1, T2>& p){
    os << "(" << p.first << ": " << p.second << ")";
    return os;
}

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
    os << kv;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const string& test_name) {
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

#define ASSERT_EQUAL(x, y) {                    \
  ostringstream osAssertMessage;                \
  osAssertMessage << #x << " != " << #y << ", " \
    << __FILE__ << ":" << __LINE__;             \
  AssertEqual(x, y, osAssertMessage.str());     \
}

#define ASSERT(x) {                        \
  ostringstream osAssertMessage;           \
  osAssertMessage << #x << " is false, "   \
    << __FILE__ << ":" << __LINE__;        \
  Assert(x, osAssertMessage.str());        \
}

#define RUN_TEST(tr, func) \
  tr.RunTest(func, #func)
