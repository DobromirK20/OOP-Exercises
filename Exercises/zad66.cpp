#include <iostream>
#include <stdexcept>
using namespace std;

int validateInput(const string& input, int min, int max) {
    int number;

    try
    {
        number = stoi(input);
    }
    catch(...)
    {
        throw invalid_argument("Not a valid argument");
    }
    
    if(number < min || number > max) {
        throw out_of_range("Number ot of range");
    }

    return number;
}