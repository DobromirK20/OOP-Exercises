#include <iostream>
using namespace std;

enum class FuelType {
    Petrol,
    Diesel,
    Electric,
    Hybrid
};

struct Car
{
    char brand[50];
    char model[50];
    unsigned int year;
    unsigned int value; 
    FuelType type;
};

void printCar(const Car& car) {
    cout<<car.brand<<endl;
    cout<<car.model<<endl;
    cout<<car.year<<endl;
    cout<<car.value<<endl;
    
    switch (car.type)
    {
    case FuelType::Petrol:
        cout<<"Petrol";
        break;
    case FuelType::Diesel:
        cout<<"Diesel";
        break;
    case FuelType::Electric:
        cout<<"Electric";
        break;
    case FuelType::Hybrid:
        cout<<"Hybrid";
        break;
    }

    cout<<endl;
}

Car findCheapest(const Car cars[], int count) {
    Car cheapest = cars[0];

    for(int i = 1; i < count; i++) {
        if(cars[i].value < cheapest.value) {
            cheapest = cars[i];
        }
    }

    return cheapest;
}

int countByFuel(const Car cars[], int count, FuelType fuel) {
    int counter = 0;

    for(int i = 0; i < count; i++) {
        if(cars[i].type == fuel) {
            counter++;
        }
    }

    return counter;
}

int main()
{
    Car cars[4] =
    {
        { "BMW", "320d", 2018, 20000, FuelType::Diesel },
        { "Tesla", "Model 3", 2022, 35000, FuelType::Electric },
        { "Toyota", "Corolla", 2020, 18000, FuelType::Hybrid },
        { "Audi", "A4", 2017, 19000, FuelType::Petrol }
    };

    cout << "Всички коли:" << endl;
    cout << "----------------" << endl;

    for (int i = 0; i < 4; i++)
    {
        printCar(cars[i]);
        cout << "----------------" << endl;
    }

    cout << endl;

    Car cheapest = findCheapest(cars, 4);

    cout << "Най-евтината кола е:" << endl;
    printCar(cheapest);

    cout << endl;

    int dieselCount = countByFuel(cars, 4, FuelType::Diesel);
    cout << "Брой дизелови коли: " << dieselCount << endl;

    return 0;
}