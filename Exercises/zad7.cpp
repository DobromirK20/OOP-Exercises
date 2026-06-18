#include <iostream>
#include <stdexcept>
#include <functional>
using namespace std;

template <typename T>
T findFirst(T* arr, int size, function <bool(int)> f) {
    for(int i = 0; i < size; i++) {
        if(f(arr[i])) {
            return arr[i];
        }
    }

    throw runtime_error("No element found");
}

int main() {
    int* numbers = new int[5]{3, 7, 2, 8, 5};
    int result = findFirst(numbers, 5, [](int n) {return n > 6; });

    cout << result << endl;

    delete[] numbers;

    return 0;
}