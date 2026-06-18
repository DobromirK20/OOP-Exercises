#include <iostream>
#include <cstring>
using namespace std;

class Worker
{
protected:
    char* name;
    double salary;

    void copy(const Worker& other) {
        salary = other.salary;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
public:
    Worker(const char* n = "", double s = 0) : salary(s) {
        name = new char[strlen(n) + 1];
        strcpy(name,n);
    }

    Worker(const Worker& other) {
        copy(other);
    }

    Worker& operator=(const Worker& other) {
        if(this != &other) {
            delete[] name;
            copy(other);
        }

        return *this;
    }

    virtual ~Worker() {
        delete[] name;
    }

    void printWorker() const {
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
    }
};

class Developer : virtual public Worker
{
protected:
    char* language;

    void copy(const Developer& other) {
        language = new char[strlen(other.language) + 1];
        strcpy(language, other.language);
    }    
public:
    Developer(const char* n = "", double s = 0, const char* l = "") : Worker(n, s) {
        language = new char[strlen(l) + 1];
        strcpy(language, l);
    }

    Developer(const Developer& other) : Worker(other) {
        copy(other);
    }

    Developer& operator=(const Developer& other) {
        if (this != &other) {
            Worker::operator=(other);

            delete[] language;
            copy(other);
        }

        return *this;
    }

    ~Developer() {
        delete[] language;
    }
};

class Manager : virtual public Worker
{
protected:
    int teamSize;

public:
    Manager(const char* n = "", double s = 0, int ts = 0) : Worker(n, s), teamSize(ts) {}
};

class TeamLead : public Developer, public Manager
{
public:
    TeamLead(const char* n = "", double s = 0, const char* l = "", int ts = 0) : Worker(n, s), Developer(n, s, l), Manager(n, s, ts) {}
    
    void describe() const
    {
        cout << "TeamLead:" << endl;
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
        cout << "Programming language: " << language << endl;
        cout << "Team size: " << teamSize << endl;
    }
};

void task4()
{
    TeamLead tl("Ivan", 5000, "C++", 8);

    tl.describe();

    cout << endl;
    cout << "Checking Worker copy:" << endl;

    tl.printWorker();
}

int main()
{
    task4();

    return 0;
}
