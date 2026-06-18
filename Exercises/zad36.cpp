#include <iostream>
using namespace std; 

class RangeIterator
{
    int current;
    int step;
public:
    RangeIterator(int c, int s) : current(c), step(s) {}

    int operator*() const {
        return current;
    }

    RangeIterator& operator++() {
        current += step;
        return *this;
    }

    bool operator!=(const RangeIterator& other) const {
        return current < other.current;
    }
};

class Range
{
    int start;
    int finish;
    int step;
public:
    Range(int s, int f, int st = 1) : start(s), finish(f), step(st) {}

    RangeIterator begin() const {
        return RangeIterator(start, step);
    }

    RangeIterator end() const {
        return RangeIterator(finish, step);
    }
};


int main() {
    for(int val : Range(1, 6)) {
        cout << val << " ";
    }
    cout << endl;

    for(int val : Range(0, 10, 2)) {
        cout << val << " ";
    }

    return 0;
}