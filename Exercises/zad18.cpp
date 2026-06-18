#include <iostream>
#include <cstring>
using namespace std;

class Complex
{
private:
    double real, imag;
public:
    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real* other.imag + imag * other.real);
    }

    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other); 
    }

    ~Complex();
};

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real;
    if(c.imag >= 0) os << "+";
    os << c.imag << "i";
    return os;
}

istream& operator>>(istream& is, Complex& c) {
    is >> c.real >> c.imag;
    return is;
}

class Counter
{
private:
    int value;
public:
    Counter(int v = 0) : value(v) {}

    Counter& operator++() {
        ++value;
        return *this;
    }

    Counter operator++(int) {
        Counter old(*this);
        ++value;
        return old;
    }
    
    int getValue() const {
        return value;
    }
};

int main() {
    return 0;
}