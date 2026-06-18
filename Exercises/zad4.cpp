#include <iostream>
using namespace std;

namespace Converter
{
    double celsiusToFahrenheit(double c) {
        return c * 9.0 / 5.0 + 32;
    }

    double fahrenheitToCelsius(double f) {
        return (f - 32) * 5.0 / 9.0;
    }
}

namespace Validator
{ 
    bool isPositive(int value) {
        return value > 0;
    }

    bool isInRange(int value, int min, int max) {
        return value >= min && value <= max;
    }
}

int main() {
    double c = 25;
    double f = Converter::celsiusToFahrenheit(c);

    cout << f << " Fahrenheit = "
         << Converter::fahrenheitToCelsius(f)
         << " Celsius" << endl;
         
    int number = 10;

    if(Validator::isPositive(number))
       cout << number << "is positive." << endl;

    if(Validator::isInRange(number,5,15))
       cout << number << "is in range [5,15]." << endl;

    return 0;
}