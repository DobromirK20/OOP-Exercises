#include <iostream>
using namespace std;

class ReverseRange
{
    int start, finish;
public:
    ReverseRange(int from, int to) : start(from), finish(to) {}

    class Iterator
    {
        int current;
    public:
        Iterator(int v) : current(v) {}
        int operator*() const { return current; }
        Iterator& operator++() { --current; return *this; }
        bool operator!=(const Iterator& o) const { return current != o.current; }
    };

    Iterator begin() const { return Iterator(finish - 1); }
    Iterator end() const { return Iterator(start - 1); }
};

int main() {
    std::cout << "Обратно броене: ";
    for (int val : ReverseRange(1, 11)) {
        std::cout << val << " ";
    }
    std::cout << std::endl;  // 10 9 8 7 6 5 4 3 2 1
    
    return 0;
}