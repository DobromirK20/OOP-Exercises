#include <iostream>
#include <vector>
using namespace std;

class Operation
{
public:
    virtual void execute() const = 0;
    virtual ~Operation() {}
};

class Add : public Operation
{
private:
    double a, b;
public:
    Add(double a, double b) {
        this->a = a;
        this->b = b;
    }

    void execute() const override {
        cout << "a + b = " << a + b << endl;
    }
};

class Multiply : public Operation
{
private:
    double a, b;
public:
    Multiply(double a, double b) {
        this->a = a;
        this->b = b;
    }

    void execute() const override {
        cout << "a * b = " << a * b << endl;
    }
};

int main() {
    vector<Operation*> operations;
    operations.push_back(new Add(2,4));
    operations.push_back(new Multiply(3,4));
    operations.push_back(new Add(1,2));

    for(Operation* op : operations) {
        op->execute();
        delete op;
    }

    return 0;
}