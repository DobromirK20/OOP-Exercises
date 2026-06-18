#include <iostream>
#include <cstring>
using namespace std;

class Shape
{
public:
    virtual Shape* clone() const = 0;
    virtual void print() const = 0;

    virtual ~Shape() {}
};

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r = 0) : radius(r) {}

    void setRadius(double r)
    {
        radius = r;
    }

    Shape* clone() const override
    {
        return new Circle(*this);
    }

    void print() const override
    {
        cout << "Circle with radius: " << radius << endl;
    }
};

class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(double w = 0, double h = 0) : width(w), height(h) {}

    void setWidth(double w)
    {
        width = w;
    }

    void setHeight(double h)
    {
        height = h;
    }

    Shape* clone() const override
    {
        return new Rectangle(*this);
    }

    void print() const override
    {
        cout << "Rectangle with width: " << width << " and height: " << height << endl;
    }
};

class ShapeRegistry
{
private:
    char** names;
    Shape** prototypes;
    int count;
    int capacity;

    void resize()
    {
        capacity *= 2;

        char** newNames = new char*[capacity];
        Shape** newPrototypes = new Shape*[capacity];

        for (int i = 0; i < count; i++)
        {
            newNames[i] = names[i];
            newPrototypes[i] = prototypes[i];
        }

        delete[] names;
        delete[] prototypes;

        names = newNames;
        prototypes = newPrototypes;
    }

public:
    ShapeRegistry() : count(0), capacity(2)
    {
        names = new char*[capacity];
        prototypes = new Shape*[capacity];
    }

    void registerShape(const char* name, Shape* prototype)
    {
        if (count == capacity)
        {
            resize();
        }

        names[count] = new char[strlen(name) + 1];
        strcpy(names[count], name);

        prototypes[count] = prototype;

        count++;
    }

    Shape* create(const char* name) const
    {
        for (int i = 0; i < count; i++)
        {
            if (strcmp(names[i], name) == 0)
            {
                return prototypes[i]->clone();
            }
        }

        return nullptr;
    }

    ~ShapeRegistry()
    {
        for (int i = 0; i < count; i++)
        {
            delete[] names[i];
        }

        delete[] names;
        delete[] prototypes;
    }
};

int main()
{
    ShapeRegistry registry;

    Circle circlePrototype(1);
    Rectangle rectPrototype(2, 3);

    registry.registerShape("circle", &circlePrototype);
    registry.registerShape("rect", &rectPrototype);

    Shape* s1 = registry.create("circle");
    Shape* s2 = registry.create("rect");

    s1->print();
    s2->print();

    Circle* c = dynamic_cast<Circle*>(s1);

    if (c != nullptr)
    {
        c->setRadius(10);
    }

    cout << "After change:" << endl;

    s1->print();
    circlePrototype.print();

    delete s1;
    delete s2;

    return 0;
}