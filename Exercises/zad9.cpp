#include <iostream>
using namespace std;

void copyStr(char* dest, const char* src) {
    int i = 0;

    while(src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

class Car
{
private:
    char* brand;
    char* model;
    int year;
    double mileage;
public:
    Car(const char* b, const char* m, int y, double km) {

        brand = new char[50];
        model = new char[50];

        copyStr(brand, b);
        copyStr(model, m);

        if(y > 1886) {
            year = y;
        }
        else {
            year = 1886;
        }

        if(km >= 0) {
            mileage = km;
        }
        else {
            mileage = 0;
        }
    }

    void drive(double km) {
        if(km > 0) {
            mileage += km;
        }
    }

    int getAge() const {
        return 2026 - year;
    }

    void print() const {
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
        cout << "Mileage: " << mileage << " km" << endl;
    }

    ~Car(){
        delete[] brand;
        delete[] model;
    }
};

int main() {
    Car c("BMW", "320d", 2018, 120000);

    c.drive(500);
    c.print();

    cout << "Age: " << c.getAge() << endl;

    return 0;
}