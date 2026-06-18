#include <iostream>
using namespace std;

class Shape
{
public:
    virtual double area() const {
        return 0;
    }

    virtual void print() const {
        cout << "Shape: " << endl;
    }

    virtual ~Shape() {}
};

class Circle : public Shape
{
private:
    double radius;
public:
    Circle(double r = 0) : radius(r) {}
    
    double area() const override {
        return 3.14 * radius * radius;
    }

    void print() const override { 
        cout << "Circle -> Area: " << area() << endl;
    }
};

class Rectangle : public Shape
{
private:
    double width;
    double height;
public:
    Rectangle(double w = 0, double h = 0) : width(w) , height(h) {}
    
    double area() const override {
        return width * height;
    }

    void print() const override {
        cout << "Rectangle -> Area: " << area() << endl;
    }
};

class Triangle : public Shape
{
private:
    double base;
    double height;
public:
    Triangle(double b = 0, double h = 0) : base(b), height(h) {}
    
    double area() const override
    {
        return (base * height) / 2;
    }

    void print() const override
    {
        cout << "Triangle -> Area: " << area() << endl;
    }
};

void task2()
{
    Shape* shapes[3];

    shapes[0] = new Circle(5);
    shapes[1] = new Rectangle(4, 6);
    shapes[2] = new Triangle(8, 3);

    double maxArea = shapes[0]->area();
    int index = 0;

    for (int i = 1; i < 3; i++)
    {
        if (shapes[i]->area() > maxArea)
        {
            maxArea = shapes[i]->area();
            index = i;
        }
    }

    cout << "Figure with biggest area:" << endl;

    shapes[index]->print();

    for (int i = 0; i < 3; i++)
    {
        delete shapes[i];
    }
}

int main() {
    task2();

    return 0;
}