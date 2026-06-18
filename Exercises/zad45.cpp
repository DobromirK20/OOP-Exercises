#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void print() const = 0;
    virtual Shape* clone() const = 0;
    virtual ~Shape() {}
};

class Rectangle : public Shape
{
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void print() const override {
        cout << "Правоъгълник (" << width << "x" << height << "), лице=" << area() << endl;
    }

    Shape* clone() const override {
        return new Rectangle(*this);
    }
};

class Triangle : public Shape {
    double a, b, c;
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}
    
    double area() const override {
        double s = (a + b + c) / 2;
        return sqrt(s * (s-a) * (s-b) * (s-c));
    }
    double perimeter() const override { 
        return a + b + c; 
    }

    void print() const override {
        cout << "Триъгълник (" << a << ", " << b << ", " << c << "), лице=" << area() << endl;
    }

    Shape* clone() const override { 
        return new Triangle(*this); 
    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    
    double area() const override { 
        return M_PI * radius * radius;
    }

    double perimeter() const override { 
        return 2 * M_PI * radius; 
    }

    void print() const override {
        cout << "Кръг (r=" << radius << "), лице=" << area() << endl;
    }

    Shape* clone() const override { 
        return new Circle(*this); 
    }
};

class ShapeCollection
{
private:
    Shape** shapes;
    int size;
    int capacity;

    void free() {
        for(int i = 0; i < size; i++) {
            delete shapes[i];
        }

        delete[] shapes;
    }

    void copy(const ShapeCollection& other) {
        size = other.size;
        capacity = other.capacity;

        shapes = new Shape*[capacity];

        for(int i = 0; i < size; i++) {
            shapes[i] = other.shapes[i]->clone();
        }
    }

    void resize() {
        capacity *= 2;
        Shape** temp = new Shape*[capacity];
        for(int i = 0; i < size; i++) {
            temp[i] = shapes[i];
        }
        delete[] shapes;
        shapes = temp; 
    }
public:
    ShapeCollection(int c = 4) : size(0), capacity(c) {
        shapes = new Shape*[capacity];
    }

    ShapeCollection(const ShapeCollection& other) {
        copy(other);
    }

    ShapeCollection& operator=(const ShapeCollection& other) {
        if(this != &other) {
            free();
            copy(other);
        }

        return *this;
    }

    ~ShapeCollection() { 
        free();
    }

    void addShape(Shape* s) {
        if(size == capacity) {
            resize();
        }

        shapes[size++] = s;
    }

    void removeAt(int index) {
        if(index < 0 || index >= size) {
            return;
        }

        delete shapes[index];

        for(int i = index; i < size - 1; i++) {
            shapes[i] = shapes[i + 1];
        }

        size--;
    }

    double getTotalArea() const{
        double total = 0;

        for(int i = 0; i < size; i++) {
            total += shapes[i]->area();
        }

        return total;
    }

    double getTotalPerimeter() const {
        double total = 0;

        for (int i = 0; i < size; i++) {
            total += shapes[i]->perimeter();
        }

        return total;
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            shapes[i]->print();
        }

        cout << "Total area: " << getTotalArea() << endl;
        cout << "Total perimeter: " << getTotalPerimeter() << endl;
    }
};

int main()
{
    ShapeCollection collection;

    collection.addShape(new Circle(5));
    collection.addShape(new Rectangle(4, 6));
    collection.addShape(new Triangle(3, 4, 5));
    collection.addShape(new Circle(2));
    collection.addShape(new Rectangle(10, 2));

    cout << "Original collection:" << endl;
    collection.print();

    ShapeCollection copy = collection;

    collection.removeAt(0);

    cout << endl;
    cout << "Modified original:" << endl;
    collection.print();

    cout << endl;
    cout << "Copied collection:" << endl;
    copy.print();

    return 0;
}