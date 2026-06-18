#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
using namespace std;

class NumberException : public runtime_error
{
public:
    NumberException(const string& mes) : runtime_error(mes){}
};

class SizeException : public NumberException
{
public:
    SizeException() : NumberException("Nedostatuchen razmer") {}
};

class NumberArray
{
private:
    int* numbers;
    int size;
public:
    NumberArray(int s) : size(s) {
        if(s <= 0) {
            throw SizeException();
        }

        numbers = new int[size];

        for(int i=0;i<size;i++){
            numbers[i] = 0;
        }
    }

    NumberArray(const NumberArray& other) {
        size = other.size;
        numbers = new int[size];

        for(int i=0; i<size; i++) {
            numbers[i] = other.numbers[i];
        }
    }

    NumberArray(NumberArray&& other) noexcept {
        size = other.size;
        numbers = other.numbers;

        other.size = 0;
        other.numbers = nullptr;
    }

    NumberArray& operator=(const NumberArray& other) {
        if(this != &other) {
            size = other.size;

            delete[] numbers;
            numbers = new int[size];

            for(int i = 0; i < size; i++) {
                numbers[i] = other.numbers[i];
            }
        }

        return *this;
    }

    NumberArray& operator=(NumberArray&& other) noexcept {
        if(this != &other) {
            size = other.size;
            delete[] numbers;
            numbers = other.numbers;
            other.size=0;
            other.numbers=nullptr;
        }

        return *this;
    }

    void print() const
    {
        if(numbers == nullptr)
        {
            cout << "Empty object\n";
            return;
        }

        for(int i = 0; i < size; i++)
        {
            cout << numbers[i] << " ";
        }

        cout << endl;
    }

    ~NumberArray() noexcept {
        delete[] numbers;
    }
};

int main()
{
    try
    {
        NumberArray a(5);

        cout << "a:" << endl;
        a.print();

        NumberArray b = a;

        cout << "b (copy of a):" << endl;
        b.print();

        NumberArray c = move(a);

        cout << "c (moved from a):" << endl;
        c.print();

        cout << "a after move:" << endl;
        a.print();
    }
    catch(const NumberException& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}

