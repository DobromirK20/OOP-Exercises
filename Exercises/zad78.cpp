#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class ProductLine
{
private:
    T initial;
    int n;
    T (*process)(T);
public:
    ProductLine(const T& i, int steps, T (*func)(T)) : initial(i), n(steps), process(func) {}

    T operator[](int index) const {
        if(index < 0 || index >= n) {
            throw out_of_range("Invalid index");
        }

        T current = initial;

        for(int i = 0; i < index; i++) {
            current = process(current);
        }

        return current;
    }

    class Iterator
    {
    private:
        const ProductLine<T>* line;
        int index;
    public:
        Iterator(int i, const ProductLine<T>* l) : index(i), line(l) {}
        
        T operator*() const {
            T current = line->initial;

            for(int i = 0; i < index; i++) {
                current = line->process(current);
            }

            return current;
        }

        Iterator& operator++() {
            ++index;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index;
        }
    };

    // class Iterator
    // {
    // private:
    //     ProductLine<T>::Iterator it;
    // public:
    //     Iterator(const ProductLine<T>& i) : it(i){}
        
    //     T operator*() {
    //         return *it;
    //     }

    //     Iterator& operator++(){
    //         ++it;
    //         return *this;
    //     }

    //     bool operator!=(const Iterator& other) const {
    //         return it != other.it;
    //     }
    // };

    Iterator begin() const {
        return Iterator(0, this);
    }

    Iterator end() const {
        return Iterator(n, this);
    }

    ~ProductLine() {}
};

int doubleUp(int x)
{
    return x * 2;
}

int main()
{
    ProductLine<int> doublingLine(1, 5, doubleUp);

    cout << "Operator []:" << endl;

    for(int i = 0; i < 5; i++)
    {
        cout << doublingLine[i] << " ";
    }

    cout << endl;

    cout << "Iterator:" << endl;

    for(auto part : doublingLine)
    {
        cout << part << " ";
    }

    cout << endl;

    return 0;
}