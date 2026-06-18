#include <iostream>
#include <vector>
using namespace std;

class Shape
{
public:
    virtual double area() const = 0;
    virtual void print(ostream& os) const = 0;
    virtual Shape* clone() const = 0;

    virtual ~Shape() {}
};

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r)
        : radius(r)
    {
    }

    double area() const override
    {
        return 3.14159 * radius * radius;
    }

    void print(ostream& os) const override
    {
        os << "Circle radius = " << radius;
    }

    Shape* clone() const override
    {
        return new Circle(*this);
    }
};

class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(double w, double h)
        : width(w), height(h)
    {
    }

    double area() const override
    {
        return width * height;
    }

    void print(ostream& os) const override
    {
        os << "Rectangle " << width << " x " << height;
    }

    Shape* clone() const override
    {
        return new Rectangle(*this);
    }
};

int main()
{
    vector<Shape*> shapes;

    Circle c1(5);
    Rectangle r1(4, 6);

    shapes.push_back(c1.clone());
    shapes.push_back(r1.clone());

    Shape* copy = shapes[0]->clone();
    shapes.push_back(copy);

    for(Shape* shape : shapes)
    {
        shape->print(cout);
        cout << " | Area = " << shape->area() << endl;
    }

    for(Shape* shape : shapes)
    {
        delete shape;
    }

    return 0;
}