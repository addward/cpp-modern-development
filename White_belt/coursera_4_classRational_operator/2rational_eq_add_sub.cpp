#include <iostream>
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

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);

        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);

        Rational b(4, 3);

        Rational c = a + b;
        bool equal = c == Rational(2, 1);

        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
