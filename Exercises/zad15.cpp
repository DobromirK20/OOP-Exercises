#include <iostream>
using namespace std;

class DynamicArray
{
private:
    double* data;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        double* newData = new double[capacity];
        for(int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
public:
    DynamicArray() : size(0), capacity(4) {
        data = new double[capacity];
    }

    DynamicArray(double* d, int s, int c) {
        if (c <= 0 || s < 0 || s > c) {
            size = 0;
            capacity = 4;
            data = new double[capacity];
            return;
        }

        size = s;
        capacity = c;
        data = new double[capacity];

        for(int i=0; i<size; i++) {
            data[i] = d[i];
        }
    }

    DynamicArray(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;
        data = new double[capacity];

        for(int i=0; i<size; i++) {
            data[i] = other.data[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if(this != &other) {
            size = other.size;
            capacity = other.capacity;

            delete[] data;
            data = new double[capacity];
            for(int i = 0; i<size; i++) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    void push(double val) {
        if(size >= capacity) {
            resize();
        }
        data[size++] = val;
    }

    void pop() {
        if(size <= 0) {
            cout << "error" << endl;
            return;
        }
        size--;
    }

    double get(int index) const {
        if (index < 0 || index >= size) {
            cout << "Invalid index!" << endl;
            return 0;
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }

    void print() const {
        cout << "Size: " << size << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Data: ";

        for (int i = 0; i < size; i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << data[i];
        }

        cout << endl;
    }

    ~DynamicArray() {
        delete[] data;
    }
};

int main() {
    DynamicArray arr;

    // Добавяме 15 елемента
    for (int i = 1; i <= 15; i++) {
        arr.push(i * 1.0);
    }

    cout << "Original: ";
    arr.print();

    // Копиране
    DynamicArray copyArr = arr;
    copyArr.push(999);

    cout << "Copy modified: ";
    copyArr.print();

    cout << "Original after copy: ";
    arr.print();

    // Присвояване
    DynamicArray assignArr;
    assignArr = arr;

    assignArr.pop();
    assignArr.push(555);

    cout << "Assigned modified: ";
    assignArr.print();

    cout << "Original after assign: ";
    arr.print();

    return 0;
}