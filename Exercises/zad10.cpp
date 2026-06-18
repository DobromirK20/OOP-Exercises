#include <iostream>
using namespace std;

class Rectangle {
private:
    double width;
    double height;
public:
    Rectangle(double w, double h) {
        if(w > 0) {
        width = w;
    } else {
        width = 1;
    }

    if(h > 0) {
        height = h;
    } else {
        height = 1;
    }
    }

    double area() const {
        return width * height;
    }

    double perimeter() const {
        return 2 * (width + height);
    }

    bool isSquare() const {
        return  width == height;
    }

    void scale(double factor) {
        if(factor > 0) {
            width *= factor;
            height *= factor;
        }
    }

    void print() const {
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
        if(isSquare()) {
            cout << "This rectangle is a square." << endl;
        } else {
            cout << "This rectangle is not a square." << endl;
        }
    }
};

Rectangle findLargest(const Rectangle rects[], int count) {
    Rectangle largest = rects[0];

    for(int i = 1; i < count; i++) {
        if(largest.area() < rects[i].area()) {
            largest = rects[i];
        }
    }

    return largest;
}

int main() {
    Rectangle rects[4] = {
        Rectangle(3, 4),
        Rectangle(5, 5),
        Rectangle(2, 10),
        Rectangle(7, 1)
    };

    cout << "All rectangles:\n\n";

    for(int i = 0; i < 4; i++) {
        rects[i].print();
        cout << "-------------------\n";
    }

    Rectangle largest = findLargest(rects, 4);

    cout << "\nRectangle with largest area:\n\n";
    largest.print();

    cout << "\nScaling first rectangle by factor 2:\n\n";
    rects[0].scale(2);
    rects[0].print();

    return 0;
}