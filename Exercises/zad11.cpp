#include <iostream>
#include <stdexcept>
using namespace std;

void copyStr(char dest[], const char src[]) {
    int i = 0;

    while(src[i] != '\0') {
        dest[i] = src[i];
        i++; 
    }

    dest[i] = '\0';
}

class Employee
{
private:
    char* name;
    char* role;
    double salary;
public:
    Employee(const char* n, const char* r, double s) {
        name = new char[100];
        role = new char[50];

        copyStr(name, n);
        copyStr(role, r);

        if(s >= 0 ) {
            salary = s;
        }
        else {
            throw runtime_error("Greshka");
        }
    }

    Employee(const Employee& other) {
        name = new char[100];
        role = new char[50];

        copyStr(name, other.name);
        copyStr(role, other.role);

        salary = other.salary;
    }

    Employee& operator=(const Employee& other) {
        if(this != &other) { 

           delete[] name;
           delete[] role;

           name = new char[100];
           role = new char[50];

           copyStr(name, other.name);
           copyStr(role, other.role);

           salary = other.salary;
        }

        return *this;
    }

    void promote(double raise) {
        if(raise > 0) {
            salary += raise;
        }
    }

    double getSalary() const {
        return salary;
    }

    void print() const {
        cout << "Name: " << name << endl;
        cout << "Position: " << role << endl;
        cout << "Salary: " << salary << endl;
    }

    ~Employee() {
        delete[] name;
        delete[] role;
    }
};

Employee findHighest(const Employee* arr, int size) {
    Employee best = arr[0];

    for(int i=0; i<size; i++) {
        if(arr[i].getSalary() > best.getSalary()) {
            best = arr[i];
        }
    }

    return best;
}

int main() {
    Employee employees[5] = {
        Employee("Ivan", "Developer", 3000),
        Employee("Maria", "Manager", 4500),
        Employee("Georgi", "Tester", 2500),
        Employee("Petar", "DevOps", 4000),
        Employee("Elena", "HR", 2800)
    };

    cout << "All employees:\n\n";

    for(int i = 0; i < 5; i++) {
        employees[i].print();
        cout << "------------------\n";
    }

    Employee highest = findHighest(employees, 5);

    cout << "\nEmployee with highest salary:\n\n";
    highest.print();

    cout << "\nPromoting first employee:\n\n";
    employees[0].promote(500);
    employees[0].print();

    return 0;
}