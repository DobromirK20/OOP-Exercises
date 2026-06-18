#include <iostream>
#include <cstring>
using namespace std;

class Engine
{
    int horsepower;
    char type[20];
public:
    Engine(int hp, const char* t) : horsepower(hp) {
        strncpy(type, t, 19);
        type[19] = '\0';
    }
    
    void start() const {
        cout << type << "dvigatel startiran (" << horsepower << "k.s.)" << endl;
    }
};

class Car {
    char brand[50];
    Engine engine;
public:
    Car(const char* b, int hp, const char* engineType) : engine(hp,engineType) {
        strncpy(brand,b,49);
        brand[49] = '\0';
    }

    void start() const {
        cout << brand << ": ";
        engine.start();
    }
};

int main() {
    Car car1("BMW", 300, "V6");
    Car car2("Tesla", 500, "Electric");

    car1.start();
    car2.start();

    return 0;
}