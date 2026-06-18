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

class OperationFactory
{
public:
    static Operation* create(const string& type, double a, double b) {
        if(type == "add") {
            return new Add(a,b);
        }
        else if(type == "mul") {
            return new Multiply(a,b);
        }

        return nullptr;
    }
};

int main() {
    vector<Operation*> operations;
    operations.push_back(OperationFactory::create("add", 2, 4));
    operations.push_back(OperationFactory::create("mul", 3, 4));
    operations.push_back(OperationFactory::create("add", 10, 20));

    for(Operation* op : operations) {
        if(op) {
            op->execute();
            delete op;
        }
    }
    
    return 0;
}