#include <iostream>
using namespace std;

class ReversibleArray
{
private:
    int* data;
    int size;
public:
    ReversibleArray(int s) : size(s) {
        data = new int[size];
    }

    ~ReversibleArray() {
        delete[] data;
    }

    int& operator[](int index) {
        return data[index];
    }

    class Iterator
    {
    private:
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

    class ReverseIterator
    {
    private:
        int* ptr;
    public:
        ReverseIterator(int* p) : ptr(p) {}

        int& operator*() {
            return *ptr;
        }

        ReverseIterator& operator++() {
            --ptr;
            return *this;
        }

        bool operator!=(const ReverseIterator& other) const {
            return ptr != other.ptr;
        }
    };
    
    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + size);
    }

    class ReverseView
    {
    private:
        ReversibleArray* arr;
    public:
        ReverseView(ReversibleArray* a) : arr(a) {}

        ReverseIterator begin() {
            return ReverseIterator(arr->data + arr->size - 1);
        }

        ReverseIterator end() {
            return ReverseIterator(arr->data - 1);
        }
    }; 
    
    ReverseView reversed() {
        return ReverseView(this);
    }
};

int main() {
    ReversibleArray arr(5);

    for (int i = 0; i < 5; i++) {
        arr[i] = (i + 1) * 10;
    }

    for (int val : arr) {
        cout << val << " ";
    }

    cout << endl;

    for (int val : arr.reversed()) {
        cout << val << " ";
    }

    return 0;
}