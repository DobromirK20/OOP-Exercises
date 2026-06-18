#include <iostream>
#include <stdexcept>
using namespace std;

class Shape
{
public:
    virtual double calculateArea() const = 0;
    virtual ~Shape(){}
};

class Circle : public Shape
{
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double calculateArea() const override {
        if(radius <= 0) {
            throw out_of_range("Radiusa ne moje da e otricatelno");
        }

        return radius * radius * 3.14;
    }
};

class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(double w, double h)
        : width(w), height(h) {}

    double calculateArea() const override
    {
        if (width <= 0 || height <= 0)
        {
            throw out_of_range("Width and height must be positive");
        }

        return width * height;
    }
};

int main() {
    try
    {
        Circle c1(3);
        Circle c2(-1);
        Rectangle r1(3,4);

        cout << c1.calculateArea() << endl;
        cout << c2.calculateArea() << endl;
        cout << r1.calculateArea() << endl;
    }
    catch(const exception& e)
    {
        cout << e.what() << '\n';
    }
    
    return 0;
}


