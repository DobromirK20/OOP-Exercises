#include <iostream>
#include <cstring>
using namespace std;

class Drawable
{
public:
    virtual void draw() const = 0;
    virtual ~Drawable() {}
};

class Circle : public Drawable
{
private:
    double radius;
public:
    Circle(double r = 0) : radius(r) {}
    
    void draw() const override {
        cout << "Drawing Circle with radius " << radius << endl;
    }
};

class Line : public Drawable
{
private:
    double length;

public:
    Line(double l = 0) : length(l) {}

    void draw() const override {
        cout << "Drawing Line with length " << length << endl;
    }
};


class Text : public Drawable
{
private:
    char* text;

    void copy(const Text& other) {
        text = new char[strlen(other.text) + 1];
        strcpy(text, other.text);
    }
public:
    Text(const char* t) {
        text = new char[strlen(t) + 1];
        strcpy(text, t);
    }

    Text(const Text& other) {
        copy(other);
    }

    Text& operator=(const Text& other) {
        if (this != &other) {
            delete[] text;
            copy(other);
        }

        return *this;
    }

    ~Text() {
        delete[] text;
    }

    void draw() const override {
        cout << "Drawing Text: " << text << endl;
    }
};

void renderAll(Drawable* items[], int count) {
    for(int i = 0; i < count; i++) {
        items[i]->draw();
    }
}

int main() {
    Drawable* items[3];

    items[0] = new Circle(5);
    items[1] = new Line(10);
    items[2] = new Text("Hello");

    renderAll(items, 3);

    for (int i = 0; i < 3; i++)
    {
        delete items[i];
    }

    return 0;
}

