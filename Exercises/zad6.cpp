#include <iostream>
#include <functional>
using namespace std;

void applyToAll(int* arr, int size, function<int(int)> f) {
    for(int i = 0; i < size; i++) {
        cout << f(arr[i]) << " ";
    }

    cout << endl;
}

int main() {
    int* numbers = new int[5]{1, 2, 3, 4, 5};

    applyToAll(numbers, 5, [](int a) {return a*3; });

    delete[] numbers;

    return 0;
}