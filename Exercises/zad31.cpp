#include <iostream>
using namespace std;

class Iterator {
    int* ptr;
public:
    Iterator(int* p) : ptr(p) {}

    int& operator*() {
        return *ptr;
    }

    Iterator& operator++() {
        ++ptr;
        return *this;
    }

    bool operator!=(const Iterator& other) const {
        return ptr != other.ptr;
    }
};

class IntArray
{
    int* data;
    int size;
public:
    IntArray(int n) : size(n) {
        data = new int[n];
    }

    int& operator[](int i) {
        return data[i];
    }

    int getSize() const {
        return size;
    }

    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + size);
    }

    ~IntArray() {
        delete[] data;
    }
};

int main() {
    IntArray arr(5);

    for(int i = 0; i < 5; i++) {
        arr[i] = (i + 1) * 10;
    }

    for(int &val : arr) {
        cout << val << " ";
    }

    return 0;
}

