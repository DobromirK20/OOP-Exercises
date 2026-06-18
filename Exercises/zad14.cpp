#include <iostream>
#include <cstring>
using namespace std;

class DynamicArray
{
private:
    int* data;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        int* newData = new int[capacity];
        for(int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    void copyFrom(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for(int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    void free() {
        delete[] data;
    }

public:
    DynamicArray() : data(new int[4]), size(0), capacity(4) {}

    DynamicArray(const DynamicArray& other) {
        copyFrom(other);
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }

        return *this;
    }

    ~DynamicArray() {
        free();
    }

    void push(int val) {
        if(size >= capacity) {
            resize();
        }

        data[size++] = val;
    }

    int pop() {
        if(size == 0) return -1;
        return data[--size];
    }

    void print() const {
        cout << "[";
        for(int i = 0; i < size; i++) {
            if(i > 0) cout << ", ";
            cout << data[i];
        }
        cout << "] (size=" << size << ", cap=" << capacity << ")" << endl;
    }
};

int main() {
    DynamicArray arr;
    for (int i = 1; i <= 10; i++) {
        arr.push(i * 10);
    }
    arr.print();  // [10, 20, 30, 40, 50, 60, 70, 80, 90, 100] (size=10, cap=16)
    
    DynamicArray copy = arr;   // Deep copy
    copy.push(110);
    copy.print();              // [10, ..., 100, 110] (size=11, cap=16)
    arr.print();               // [10, ..., 100] (size=10) — непроменен!
    
    return 0;
}

