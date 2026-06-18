#include <iostream>
#include <stdexcept>
using namespace std;

class Complex
{
private:
    double real;
    double imag;
public:
    Complex(double r = 0, double i= 0) noexcept : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;

        if(denominator == 0) {
            throw runtime_error("Division by zero complex number!");
        }

        return Complex((real * other.real + imag * other.imag) / denominator, (imag * other.real - real * other.imag) / denominator);
    }

    void print() const
    {
        cout << real;

        if (imag >= 0)
            cout << " + " << imag << "i";
        else
            cout << " - " << -imag << "i";

        cout << endl;
    }

    void setReal(const double real) noexcept {
        this->real = real;
    }

    void setImag(const double imag) noexcept {
        this->imag = imag;
    }

    double getReal() const noexcept {
        return real;
    }

    double getImag() const noexcept {
        return imag;
    }

    ~Complex() noexcept {}
};

int main() {
    try {
        Complex c1(4, 2);
        Complex c2(1, -3);

        cout << "c1 = ";
        c1.print();

        cout << "c2 = ";
        c2.print();

        Complex sum = c1 + c2;
        cout << "\nc1 + c2 = ";
        sum.print();

        Complex diff = c1 - c2;
        cout << "c1 - c2 = ";
        diff.print();

        Complex mult = c1 * c2;
        cout << "c1 * c2 = ";
        mult.print();

        Complex div = c1 / c2;
        cout << "c1 / c2 = ";
        div.print();

        Complex zero;

        cout << "\nTrying division by zero:\n";

        Complex test = c1 / zero; 
        test.print();
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
    return 0;
}
