#include <iostream>
#include <math.h>

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
        cout << gcd << endl;
        denominator = denominator / gcd;
        numerator= numerator / gcd;
        if (denominator < 0) {
            denominator *= -1;
            numerator *= -1;
        }
    }
    int GCD(int a, int b){
        while (a != 0 && b != 0) {
            cout << a << " " << b << endl;
            if (a <= b) {
                b = b % a;
            } else {
                a = a % b;
            }
    }
    return a + b;
}
};

int main() {
    {
        const Rational r(4, 3);
        if (r.Numerator() != 4 || r.Denominator() != 3) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(-4, -6);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
