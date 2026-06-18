#include <iostream>
#include <cstring>
using namespace std;

class Vehicle
{
protected:
    char* brand;
    int year;
    int maxSpeed;

    void copy(const Vehicle& other) {
        year = other.year;
        maxSpeed = other.maxSpeed;
        brand = new char[strlen(other.brand) + 1];
        strcpy(brand, other.brand);
    }
public:
    Vehicle(const char* b = "", int y = 0, int ms = 0) : year(y), maxSpeed(ms) {
        brand = new char[strlen(b) + 1];
        strcpy(brand, b);
    }

    Vehicle(const Vehicle& other) {
        copy(other);
    }

    Vehicle& operator=(const Vehicle& other) {
        if(this != &other) {
            delete[] brand;
            copy(other);
        }

        return *this;
    }

    virtual void describe() const {
        cout << "Brand: " << brand << endl;
        cout << "Year: " << year << endl;
        cout << "Max speed: " << maxSpeed << endl;
    }

    virtual ~Vehicle() {
        delete[] brand;
    }
};

class Car : public Vehicle
{
private:
    int doors;
public:
    Car(const char* b = "", int y = 0, int ms = 0, int d = 0) : Vehicle(b, y, ms), doors(d) {}

    void describe() const override {
        cout << "Brand: " << brand << endl;
        cout << "Year: " << year << endl;
        cout << "Max speed: " << maxSpeed << endl;
        cout << "Doors: " << doors << endl;
    }    
};

class Truck : public Vehicle
{
private:
    double capacity;
public:
    Truck(const char* b = "", int y = 0, int ms = 0, double c = 0) : Vehicle(b, y, ms), capacity(c) {}
    
    void describe() const override {
        cout << "Brand: " << brand << endl;
        cout << "Year: " << year << endl;
        cout << "Max speed: " << maxSpeed << endl;
        cout << "Capacity: " << capacity << endl;
    }
};

class Motorcycle : public Vehicle
{
private:
    char* type;

    void copy(const Motorcycle& other) {
        type = new char[strlen(other.type) + 1];
        strcpy(type, other.type);
    }
public:
    Motorcycle(const char* b = "", int y = 0, int ms = 0, const char* t = "") : Vehicle(b, y, ms) {
        type = new char[strlen(t) + 1];
        strcpy(type, t);
    }

    Motorcycle(const Motorcycle& other) : Vehicle(other) {
        copy(other);
    }

    Motorcycle& operator=(const Motorcycle& other) {
        if(this != &other) {
            Vehicle::operator=(other);
            delete[] type;
            copy(other);
        }

        return *this;
    }

    void describe() const override
    {
        cout << "Motorcycle:" << endl;

        cout << "Brand: " << brand << endl;
        cout << "Year: " << year << endl;
        cout << "Max speed: " << maxSpeed << endl;
        cout << "Type: " << type << endl;
    }

    ~Motorcycle() {
        delete[] type;
    }
};

void task3() {
    Car c("BMW", 2022, 250, 4);
    Truck t("MAN", 2019, 180, 12000);
    Motorcycle m("Yamaha", 2021, 300, "Sport");

    c.describe();
    cout << endl;

    t.describe();
    cout << endl;

    m.describe();
    cout << endl;
}

int main() {
    task3();

    return 0;
}