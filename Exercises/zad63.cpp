#include <iostream>
#include <vector>
using namespace std;

class MathExpression
{
public:
    virtual double value() const = 0;
    virtual void print(ostream& os) const = 0; 
    virtual MathExpression* clone() const = 0;
    virtual ~MathExpression() {}
};

class Constant : public MathExpression
{
private:
    double con;
public:
    Constant(double c) : con(c){}

    double value() const override {
        return con;
    }

    void print(ostream& os) const override {
        os << con;
    }

    MathExpression* clone() const override {
        return new Constant(*this);
    }
};

class Min : public MathExpression
{
private:
    MathExpression* x;
    MathExpression* y;
public:
    Min(const MathExpression& x, const MathExpression& y) {
        this->x = x.clone();
        this->y = y.clone();
    }

    Min(const Min& other) {
        x = other.x->clone();
        y = other.y->clone();
    }

    Min& operator=(const Min& other) {
        if(this != &other) {
            delete x;
            delete y;

            x = other.x->clone();
            y = other.y->clone();
        }

        return *this;
    }

    double value() const override {
        return (x->value() < y->value()) ? x->value() : y->value();
    }

    void print(ostream& os) const override {
        os << "min(";
        x->print(os);
        os << ", ";
        y->print(os);
        os << ")";
    }

    MathExpression* clone() const override {
        return new Min(*this);
    }

    ~Min() {
        delete x;
        delete y;
    }
};

class Sum : public MathExpression
{
private:
    vector<MathExpression*> expressions;
public:
    Sum() {}

    Sum(const Sum& other){
        for(MathExpression* e : other.expressions) {
            expressions.push_back(e->clone());
        }
    }

    Sum& operator=(const Sum& other) {
        if(this != &other) {
            for(MathExpression* e : expressions) {
                delete e;
            }

            expressions.clear();

            for(MathExpression* e : other.expressions) {
                expressions.push_back(e->clone());
            }
        }

        return *this;
    }

    void addExpression(const MathExpression& e) {
        expressions.push_back(e.clone());
    }

    double value() const override {
        double result = 0;

        for(MathExpression* e : expressions) {
            result += e->value();
        }

        return result;
    }

    void print(ostream& os) const override {
        os << "sum(";

        for(size_t i = 0; i < expressions.size(); i++) {
            expressions[i]->print(os);

            if(i+1 < expressions.size()) {
                os << ", ";
            }
        }

        os << ")";
    }

    MathExpression* clone() const override {
        return new Sum(*this);
    }

    class Iterator
    {
    private:
        vector<MathExpression*>::iterator it;
    public:
        Iterator(vector<MathExpression*>::iterator it) {
            this->it = it;
        }

        MathExpression& operator*() const {
            return **it;
        }

        Iterator& operator++() {
            ++it;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }
    };

    Iterator begin() {
        return Iterator(expressions.begin());
    }

    Iterator end() {
        return Iterator(expressions.end());
    }

    ~Sum() {
        for(MathExpression* e : expressions) {
            delete e;
        }
    }
};
