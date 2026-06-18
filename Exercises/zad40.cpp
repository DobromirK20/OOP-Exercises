#include <iostream>
#include <cstring>
using namespace std;

class Animal
{
protected:
    char* name;
    int age;

    void copy(const Animal& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name,other.name);
        age = other.age;
    }
public:
    Animal(const char* n = "", int a = 0) : age(a) {
        name = new char[strlen(n) + 1];
        strcpy(name,n);
    }

    Animal(const Animal& other) {
        copy(other);
    }

    Animal& operator=(const Animal& other) {
        if(this != &other) {
            delete[] name;
            copy(other);
        }

        return *this;
    }

    virtual ~Animal() {
        delete[] name;
    }

    virtual void makeSound() const {
        cout << "Animal sound" << endl;
    }
};

class Dog : public Animal 
{
private:
    char* breed;

    void copy(const Dog& other) {
        breed = new char[strlen(other.breed) + 1];
        strcpy(breed,other.breed);
    }

public:
    Dog(const char* n = "", int a = 0, const char* b = "") : Animal(n, a) {
        breed = new char[strlen(b) + 1];
        strcpy(breed,b);
    }

    Dog(const Dog& other) : Animal(other) {
        copy(other);
    }

    Dog& operator=(const Dog& other) {
        if(this != &other) {
            Animal::operator=(other);

            delete[] breed;

            copy(other);
        }

        return *this;
    }

    ~Dog() {
        delete[] breed;
    }

    void makeSound() const override {
        cout << "Bau!" << endl;
    }
};

class Cat : public Animal
{
private:
    char* color;

    void copy(const Cat& other) {
        color = new char[strlen(other.color) + 1];
        strcpy(color, other.color);
    }
public:
    Cat(const char* n = "", int a = 0, const char* c = "") : Animal(n, a) {
        color = new char[strlen(c) + 1];
        strcpy(color, c);
    }

    Cat(const Cat& other) : Animal(other) {
        copy(other);
    }

    Cat& operator=(const Cat& other) {
        if(this != &other) {
            Animal::operator=(other);

            delete[] color;

            copy(other);
        }

        return *this;
    }

    ~Cat() {
        delete[] color;
    }

    void makeSound() const override {
        cout << "Mqu!" << endl;
    }
};

class Bird : public Animal
{
private:
    double wingspan;
public:
    Bird(const char* n = "", int a = 0, double w = 0) : Animal(n ,a), wingspan(w) {}
    
    void makeSound() const override { 
        cout << "Chirik! " << endl;
    }
};

void task1()
{
    Dog dogs[2] =
    {
        Dog("Rex", 3, "Husky"),
        Dog("Max", 5, "Bulldog")
    };

    Cat cats[2] =
    {
        Cat("Maca", 2, "White"),
        Cat("Luna", 4, "Black")
    };

    Bird birds[2] =
    {
        Bird("Rio", 1, 25.5),
        Bird("Kiki", 2, 18.0)
    };

    cout << "Dogs:" << endl;

    for (int i = 0; i < 2; i++)
    {
        dogs[i].makeSound();
    }

    cout << endl;

    cout << "Cats:" << endl;

    for (int i = 0; i < 2; i++)
    {
        cats[i].makeSound();
    }

    cout << endl;

    cout << "Birds:" << endl;

    for (int i = 0; i < 2; i++)
    {
        birds[i].makeSound();
    }
}

int main() {
    task1();
    
    return 0;
}