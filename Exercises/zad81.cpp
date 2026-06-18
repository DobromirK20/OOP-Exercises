#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class RotatingVector
{
private:
    vector<T> data;
    int start;
public:
    RotatingVector(const vector<T>& d, int s= 0) : data(d), start(s) {}

    vector<T> current() const {
        vector<T> result;

        for(int i = 0; i < data.size(); i++) {
            int index = (start + i) % data.size();
            result.push_back(data[index]);
        }

        return result;
    }

    RotatingVector& operator++() {
        if(!data.empty()){
            start = (start + 1) % data.size(); 
        }

        return *this;
    }

    RotatingVector& operator--() {
        if(!data.empty()){
            start = (start - 1 + data.size()) % data.size();
        }

        return *this;
    }

    friend ostream& operator<<(ostream& os, const RotatingVector<T>& rt) {
        vector<T> rotated = rt.current();

        for(T d : rotated) {
            os << d << " ";
        }

        return os;
    }
};

int main()
{
    vector<int> data = {1, 2, 3, 4, 5};

    RotatingVector<int> v(data);

    ++v;
    ++v;

    cout << v << " | ";

    ++v;
    ++v;
    --v;

    cout << v;

    return 0;
}
