#include <iostream>
#include <cstring>
using namespace std;

class Employee
{
public:
    virtual double getSalary() const = 0;

    virtual void print() const = 0;
    
    virtual ~Employee() {}
};

class Developer : public Employee
{
private:
    double salary;
    double bonus;
public:
    Developer(double s = 0, double b = 0) : salary(s), bonus(b) {}

    double getSalary() const override {
        return salary + bonus;
    }

    void print() const override
    {
        cout << "Developer salary: "
             << getSalary() << endl;
    }
};

class Manager : public Employee
{
private:
    double salary;
    double bonus;
public:
    Manager(double s = 0, double b = 0) : salary(s), bonus(b) {}
    
    double getSalary() const override {
        return salary + bonus;
    }

    void print() const override {
        cout << "Manager salary: "
             << getSalary() << endl;
    }
};

class Intern : public Employee
{
private:
    double scholarship;
public:
    Intern(double s = 0) : scholarship(s) {}
    
    double getSalary() const override {
        return scholarship;
    }

    void print() const override {
        cout << "Intern salary: "
             << getSalary() << endl;
    }
};

int main() {
    Employee* employees[3];

    employees[0] = new Developer(4000, 300);
    employees[1] = new Manager(5000, 800);
    employees[2] = new Intern(1200);

    double total = 0;

    for(int i = 0; i < 3; i++) {
        employees[i]->print();
        total+=employees[i]->getSalary();
    }

    cout << endl;
    cout << "Total salary fund: " << total << endl;

    for (int i = 0; i < 3; i++) {
        delete employees[i];
    }

    return 0;
}

