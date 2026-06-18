#include <iostream>
#include <cstring>
using namespace std;

class Animal
{
public:
    virtual void makeSound() const = 0;

    virtual ~Animal() {}
};

class Dog : public Animal
{
public:
    void makeSound() const override {
        cout << "Woof!" << endl;
    }
};

class Cat : public Animal
{
public:
    void makeSound() const override {
        cout << "Meow!" << endl;
    }
};

class Bird : public Animal
{
public:
    void makeSound() const override {
        cout << "Tweet!" << endl;
    }
};

class AnimalFactory
{
public:
    static Animal* createAnimal(const char* type) {
        if(strcmp(type, "dog") == 0) return new Dog();
        if(strcmp(type, "cat") == 0) return new Cat();
        if(strcmp(type, "bird") == 0) return new Bird();
        return nullptr;
    }
};

int main() {
    int n;
    cin >> n;

    Animal** animals = new Animal*[n];

    for(int i = 0; i < n; i++) {
        char* type = new char[20];
        cin >> type;
        animals[i] = AnimalFactory::createAnimal(type);
        delete[] type;
    }

    for(int i = 0; i < n; i++) {
        if(animals[i] != nullptr) {
            animals[i]->makeSound();
        }
    }

    for(int i = 0; i < n; i++) {
        delete animals[i];
    }
    delete[] animals;

    return 0;
}