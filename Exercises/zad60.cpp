#include <iostream>
#include <vector>
using namespace std;

template <typename T>
T maxElement(vector<T> elements) {
    T max = elements[0];

    for(size_t i = 0; i < elements.size(); i++) {
        if(elements[i] > max) {
            max = elements[i];
        }
    }

    return max;
};

int main() {
    vector<int> v1 = {1,2,10,3,5,2,4,7,9};
    vector<double> v2 = {1.5, 7.2, 3.8, 4.1};
    vector<string> v3 = {"apple", "banana", "orange"};

    cout << maxElement(v1) << endl;
    cout << maxElement(v2) << endl;
    cout << maxElement(v3) << endl;

    return 0;
}