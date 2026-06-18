#include <iostream>
#include <vector>
using namespace std;

class MathExpression
{
public:
    virtual double value() const = 0;
    virtual void print(ostream& os) const = 0;
    virtual ~MathExpression() {}

    friend ostream& operator<<(ostream& os, const MathExpression& expr) {
        expr.print(os);
        return os;
    }
};

class Constant : public MathExpression
{
private:
    double number;
public:
    Constant(double n) : number(n) {}

    double value() const override {
        return number;
    }
    
    void print(ostream& os) const override {
        os << number;
    }
};

class Min : public MathExpression
{
private:
    MathExpression* left;
    MathExpression* right;
public:
    Min(MathExpression* l, MathExpression* r) : left(l), right(r) {}

    double value() const override {
        return (left->value() < right->value()) ? left->value() : right->value();
    }

    void print(ostream& os) const override {
        os << "min(";
        left->print(os);
        os << ", ";
        right->print(os);
        os << ")";
    }

    ~Min() {
        delete left;
        delete right;
    }
};

class Sum : public MathExpression
{
private:
    vector<MathExpression*> expressions;
public:
    void addExpression(MathExpression* e) {
        expressions.push_back(e);
    }

    double value() const override {
        double result = 0;

        for(MathExpression* expr : expressions) {
            result += expr->value();
        }

        return result;
    }

    void print(ostream& os) const override {
        os << "sum(";
        for(size_t i = 0; i < expressions.size(); i++) {
            expressions[i]->print(os);

            if(i + 1 < expressions.size()) {
                os << ", ";
            }
        }

        os <<")";
    }

    ~Sum() {
        for(MathExpression* expr : expressions) {
            delete expr;
        }
    }

    auto begin() {
        return expressions.begin();
    }

    auto end() {
        return expressions.end();
    }
};

int main() {
    Sum* root = new Sum();

    Sum* sum1 = new Sum();
    sum1->addExpression(new Constant(1));
    sum1->addExpression(new Constant(2));

    root->addExpression(new Min(new Constant(1), sum1));

    Sum* sum2 = new Sum();
    sum2->addExpression(new Constant(3));
    sum2->addExpression(new Constant(4));
    sum2->addExpression(new Constant(5));

    root->addExpression(sum2);

    root->addExpression(new Constant(10));

    cout << *root;

    delete root;

    return 0;
}




