#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Tracer
{
public:
    Tracer()
    {
        cout << "Default constructor" << endl;
    }

    Tracer(const Tracer& other)
    {
        cout << "Copy constructor" << endl;
    }

    Tracer(Tracer&& other) noexcept
    {
        cout << "Move constructor" << endl;
    }

    Tracer& operator=(const Tracer& other)
    {
        cout << "Copy operator=" << endl;
        return *this;
    }

    Tracer& operator=(Tracer&& other) noexcept
    {
        cout << "Move operator=" << endl;
        return *this;
    }

    ~Tracer()
    {
        cout << "Destructor" << endl;
    }
};

int main() {
    vector<Tracer> v;

    Tracer x;

    v.push_back(x);
    v.push_back(move(x));
    v.emplace_back();

    return 0;
}