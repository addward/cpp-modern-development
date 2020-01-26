#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator) {
        this->denominator = denominator;
        this->numerator= numerator;
        simplify();
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
};

Rational operator+(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()){
        return true;
    } else {
        return false;
    }
}

Rational operator*(const Rational& lhs, const Rational& rhs){
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs){
    return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

ostream& operator<<(ostream & stream, const Rational & n){
    stream << n.Numerator() << "/" << n.Denominator();
    return stream;
}

istream& operator>>(istream & stream, Rational & n){
    int a, b;
    if (stream >> a && stream.ignore(1) && stream >> b){
        n = Rational(a, b);
    } else {
        return stream;
    }
    return stream;
}

bool operator>(const Rational& lhs, const Rational& rhs){
    Rational diff = lhs - rhs;
    if (diff.Numerator() < 0) {
        return false;
    } else {
        return true;
    }
}

bool operator<(const Rational& lhs, const Rational& rhs){
    Rational diff = lhs - rhs;
    if (diff.Numerator() < 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
