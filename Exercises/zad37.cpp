#include <iostream>
using namespace std;

class DynamicArray
{
private:
    int* data;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        int* temp = new int[capacity];
        for(int i = 0; i < size; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
public:
    DynamicArray(int cap = 2) : size(0), capacity(cap) {
        data = new int[capacity];
    } 

    DynamicArray(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for(int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if(this != &other) {
            size = other.size;
            capacity= other.capacity;
            delete[] data;
            data = new int[capacity];
            for(int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    ~DynamicArray() {
        delete[] data;
    }

    void pushBack(int value) {
        if(size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    void popBack() {
        if(size > 0) {
            size--;
        }
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    int& operator[](int index) {
        return data[index];
    }

    const int& operator[](int index) const {
        return data[index];
    }

    class Iterator
    {
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

    class ConstIterator
    {
        const int* ptr;
    public:
        ConstIterator(const int* p) : ptr(p) {}

        const int& operator*() const {
            return *ptr;
        }

        ConstIterator& operator++() {
            ++ptr;
            return *this;
        }

        bool operator!=(const ConstIterator& other) const {
            return ptr != other.ptr;
        }
    };

    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + size);
    }

    ConstIterator begin() const {
        return ConstIterator(data);
    }

    ConstIterator end() const {
        return ConstIterator(data + size);
    }

    void print() {
        for (const int& val : *this) {
            cout << val << " ";
        }

        cout << endl;
    }
};

int main() {
    DynamicArray arr;

    arr.pushBack(10);
    arr.pushBack(20);
    arr.pushBack(30);
    arr.pushBack(40);
    arr.pushBack(50);

    for (int& val : arr) {
        cout << val << " ";
    }

    cout << endl;

    for (int& val : arr) {
        val += 1;
    }

    arr.print();

    return 0;
}