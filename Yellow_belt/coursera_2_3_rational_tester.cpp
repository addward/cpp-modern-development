#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
/*
class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator) {
        if (denominator == 0){
            throw invalid_argument("a");
        } else {
            this->denominator = denominator;
            this->numerator= numerator;
            simplify();
        }
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator, denominator;
    void simplify(){
        int gcd = GCD(abs(numerator), abs(denominator));
        denominator = denominator / gcd;
        numerator= numerator / gcd;
        if (denominator < 0) {
            denominator *= -1;
            numerator *= -1;
        }
    }
    int GCD(int a, int b){
        while (a != 0 && b != 0) {
            if (a <= b) {
                b = b % a;
            } else {
                a = a % b;
            }
    }
    return a + b;
}
};*/

bool operator!=(const Rational& lhs, const Rational& rhs) {
    if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()){
        return false;
    } else {
        return true;
    }
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

ostream& operator << (ostream& os, const Rational r){
    os << r.Numerator() << "/" << r.Denominator();
    return os;
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

void test_empty_constructor(){
    Rational r;
    AssertEqual(r.Numerator(), 0, "Numerator of empty constructor");
    AssertEqual(r.Denominator(), 1, "Denominator of empty constructor");
}

void test_unsimlified_number(){
    {
        Rational r(4,2);
        AssertEqual(r, Rational(2,1), "Nonsimplified rational number 4/2");
    }
    {
        Rational r(9,3);
        AssertEqual(r, Rational(3,1), "Nonsimplified rational number 9/3");
    }
}

void test_negative_number(){
    {
        Rational r(4, -2);
        AssertEqual(r, Rational(-2,1), "Negative number 4/-2");
    }
    {
        Rational r(-4, -2);
        AssertEqual(r, Rational(2,1), "Positive number -4/-2");
    }
    {
        Rational r(-4, 2);
        AssertEqual(r, Rational(-2,1), "Positive number -4/-2");
    }
}

void test_zero_numerator(){
    {
        Rational r(0, 10);
        AssertEqual(r, Rational(0,1), "Rational number with zero numerator");
    }
    {
        Rational r(0, -10);
        AssertEqual(r, Rational(0,1), "Rational number with zero numerator and negative denominator");
    }
}

int main() {
  TestRunner runner;
  runner.RunTest(test_empty_constructor, "Empty constructor");
  runner.RunTest(test_negative_number, "Negative number");
  runner.RunTest(test_unsimlified_number, "Non-simplified number");
  runner.RunTest(test_zero_numerator, "Zero numerator");
  return 0;
}
