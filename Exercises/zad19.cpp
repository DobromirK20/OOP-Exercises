#include <iostream>
using namespace std;

class Fraction
{
private:
    int numerator;
    int denominator;

    static int absValue(int val) {
        if(val < 0) {
            return -val;
        }
        else {
            return val;
        }
    }

    static int gcd(int a, int b) {
        a = absValue(a);
        b = absValue(b);

        while(b != 0) {
            int temp = a % b;
            a = b;
            b = temp;
        }

        return a == 0 ? 1 : a; 
    }

public:
    Fraction() : numerator(0) , denominator(1) {}

    Fraction(int n, int d) {
        numerator = n;
        denominator = d;

        if(denominator == 0) {
            cout << "Error" <<endl;
            denominator = 1;
        }

        if(denominator < 0) {
            numerator = -numerator;
            denominator = - denominator;
        }

        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
    }

    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            cout << "Error" << endl;
            return Fraction(0, 1);
        }

        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }

    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator>(const Fraction& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }

    friend ostream& operator<<(ostream& os, const Fraction& f);
    friend istream& operator>>(istream& is, Fraction& f);
};

ostream& operator<<(ostream& os, const Fraction& f) {
    os << f.numerator << "/" << f.denominator;
    return os;
}

istream& operator>>(istream& is, Fraction& f) {
    char slash;

    is >> f.numerator >> slash >> f.denominator;

    if (slash != '/') {
        cout << "Invalid format! Use n/d" << endl;
        return is;
    }

    if (f.denominator == 0) {
        cout << "Error" << endl;
        f.numerator = 0;
        f.denominator = 1;
    }

    if (f.denominator < 0) {
        f.numerator = -f.numerator;
        f.denominator = -f.denominator;
    }
    
    int divisor = Fraction::gcd(f.numerator, f.denominator);
    f.numerator /= divisor;
    f.denominator /= divisor;

    return is;
}

int main() {
    Fraction a(1, 2);
    Fraction b(1, 3);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;

    Fraction c;
    cout << "\nEnter fraction in format n/d: ";
    cin >> c;
    cout << "You entered: " << c << endl;

    if (a == b) cout << "a == b" << endl;
    if (a != b) cout << "a != b" << endl;
    if (a > b)  cout << "a > b" << endl;
    if (a < b)  cout << "a < b" << endl;

    return 0;
}