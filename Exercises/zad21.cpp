#include <iostream>
#include <cstring>
using namespace std;

class BigInteger
{
private:
    char* digits;
    int size;

    void copyFrom(const BigInteger& other) {
        size = other.size;
        digits = new char[size];

        for(int i = 0; i < size; i++) {
            digits[i] = other.digits[i];
        }
    }

    void free() {
        delete[] digits;
    }

public:
    BigInteger() : size(1), digits(new char[size]) {
        digits[0] = '0';
    }

    BigInteger(const char* d) {
        size = strlen(d);
        digits = new char[size];

        for(int i = 0; i < size; i++) {
            if(d[i] < '0' || d[i] > '9') {
                cout << "Error" << endl;
                size = 1;
                delete[] digits;
                digits = new char[1];
                digits[0] = '0';
                return;
            }
            else { 
                digits[size - i - 1] = d[i];
            }
        }
    }

    BigInteger(const BigInteger& other) {
        copyFrom(other);
    }

    BigInteger& operator=(const BigInteger& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }

        return *this;
    }

    ~BigInteger() {
        free();
    }

    BigInteger operator+(const BigInteger& other) const {
        int maxSize = (size > other.size) ? size : other.size;
        BigInteger result;
        delete[] result.digits;
        result.size = maxSize;
        result.digits = new char[maxSize + 1];
        int add = 0;

        for(int i = 0; i < maxSize; i++) {
            int d1 = (i < size) ? digits[i] - '0' : 0;
            int d2 = (i < other.size) ? other.digits[i] - '0' : 0;

            if(d1 + d2 + add < 10) {
                result.digits[i] = (d1 + d2 + add) + '0';
            }
            else {
                result.digits[i] = ((d1 + d2 + add) % 10) + '0';
            }

            add = (d1 + d2 + add) / 10;
        }

        if(add != 0) {
            result.digits[maxSize] = add + '0';
            result.size = maxSize + 1;
        }

        return result;
    }

    bool operator==(const BigInteger& other) const {
        if(size != other.size) return false;

        for(int i = 0; i < size; i++) {
            if(digits[i] != other.digits[i]) return false;
        }

        return true;
    }

    bool operator<(const BigInteger& other) const {
        if(size > other.size) return false;
        if(size < other.size) return true;
        
        for(int i = size - 1; i >= 0; i++) {
            
            if(digits[i] < other.digits[i]) return true;
            if(digits[i] > other.digits[i]) return false;
        }

        return false;
    }

    friend ostream& operator<<(ostream& os, const BigInteger& c);
};

ostream& operator<<(ostream& os, const BigInteger& b) {
    for(int i = b.size - 1; i >=0; i--) {
        os << b.digits[i];
    }

    return os;
}

int main() {
    BigInteger a("999");
    BigInteger b("1");
    BigInteger c = a + b;

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    return 0;
}