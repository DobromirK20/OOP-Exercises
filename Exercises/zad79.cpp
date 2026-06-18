#include <iostream>
#include <vector>
using namespace std;


//Container : size capacity data
// Base: Animal 
// Inherit : Dog, Cat, Fish
//Container : Animal** -> Dog, Cat, Fish move semantics

class Task
{
public:
    Task(){}
    virtual Task* clone() const = 0;
    virtual int totalTime() const = 0; 
    virtual void printSchedule() const = 0;
    virtual ~Task(){}
};

class MachineTask : public Task
{
private:
    string name;
    int time;
public:
    MachineTask(const string& n, int t) : name(n), time(t) {}

    int totalTime() const override {
        return time;
    }

    Task* clone() const override{
        return new MachineTask(*this);
    }

    void printSchedule() const override {
        cout << name << " - " << time << " min" << endl; 
    }
};

class ComplexOperation : public Task
{
private:
    string name;
    vector<Task*> operations;
public:
    ComplexOperation(const string& n) : name(n) {}

    void add(const Task& o) {
        operations.push_back(o.clone());
    }

    ComplexOperation(const ComplexOperation& other) {
        name = other.name;

        for(Task* o : other.operations) {
            operations.push_back(o->clone());
        }
    }

    ComplexOperation& operator=(const ComplexOperation& other) {
        if(this != &other) {
            name = other.name;

            for(Task* o : operations) {
                delete o;
            }

            operations.clear();

            for(Task* o : other.operations) {
                operations.push_back(o->clone());
            }
        }

        return *this;
    }

    Task* clone() const override {
        return new ComplexOperation(*this);
    }

    int totalTime() const override {
        int result = 0;

        for(Task* o : operations) {
            result += o->totalTime();
        }

        return result;
    }

    void printSchedule() const override
    {
        for(Task* o : operations)
        {
            o->printSchedule();
        }
    }

    ~ComplexOperation() {
        for(Task* o : operations) {
            delete o;
        }
    }
};

int main() {
    ComplexOperation o("Proizvodstvo na smartfon");
    ComplexOperation o1("Sglobqvane na korpus");
    ComplexOperation o2("Instalirane na softuer");
    MachineTask o3("Kraino testvane", 30);
    MachineTask m1("Izrqzvane na chasti", 20);
    MachineTask m2("Sglobqvane na ramka", 10);
    MachineTask m3("Kachvane na OS", 5);
    MachineTask m4("Kachvane na softuer", 15);

    o1.add(m1);
    o1.add(m2);
    o2.add(m3);
    o2.add(m4);
    o.add(o1);
    o.add(o2);
    o.add(o3);

    int total = 0;
    total = o.totalTime();

    cout << "Total time: " << total << endl;
    o.printSchedule();

    return 0;
}