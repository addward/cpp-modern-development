#include <iostream>
#include <exception>

using namespace std;

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
    if (rhs.Numerator() == 0){
        throw domain_error("a");
    } else {
        return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
    }
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

// Вставьте сюда реализацию operator / для класса Rational

int main() {
    Rational r1, r2;
    char operation;

    try {
        cin >> r1 >> operation >> r2;
    } catch (invalid_argument&) {
        cout << "Invalid argument" << endl;
        return 1;
    }

    if (operation == '+') {
        cout << r1 + r2 << endl;
    } else if (operation == '-') {
        cout << r1 - r2 << endl;
    } else if (operation == '*') {
        cout << r1 * r2 << endl;
    } else if (operation == '/') {
        try{
            cout << r1 / r2 << endl;
        } catch (domain_error&){
            cout << "Division by zero" << endl;
            return 1;
        }
    }
    return 0;
}
