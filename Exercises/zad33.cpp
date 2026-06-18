#include <iostream>
using namespace std;

class IntArray
{
    int* data;
    int size;
public:
    IntArray(int n) : size(n) {
        data = new int[size];
    }

    IntArray(const IntArray& other) : size(other.size) {
        data = new int[size];
        for(int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    IntArray& operator=(const IntArray& other) {
        if(this != &other) {
            delete[] data;
            size = other.size;
            for(int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~IntArray() {
        delete[] data;
    }

    int& operator[](int i) {
        return data[i];
    }

    const int& operator[](int i) const {
        return data[i];
    }

    int getSize() const {
        return size;
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

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++ptr;
            return tmp;
        }

        bool operator!=(const Iterator& o) const {
            return ptr != o.ptr;
        }

        bool operator==(const Iterator& o) const {
            return ptr == o.ptr;
        }
    };
    
    class ConstIterator
    {
        const int* ptr;
    public:
        ConstIterator(const int* p) : ptr(p) {}

        const int& operator*() {
            return *ptr;
        }

        ConstIterator& operator++() {
            ++ptr;
            return *this;
        }

        bool operator!=(const ConstIterator& o) const {
            return ptr != o.ptr;
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
};

int main() {
    IntArray arr(5);
    for (int i = 0; i < 5; i++) arr[i] = (i + 1) * 10;
    
    // Range-based for
    std::cout << "Елементи: ";
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;  // 10 20 30 40 50
    
    // Модификация чрез итератор
    for (int& val : arr) {
        val *= 2;
    }
    
    std::cout << "Удвоени: ";
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;  // 20 40 60 80 100
    
    return 0;
}
