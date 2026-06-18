#include <iostream>
#include <functional>
using namespace std;

int countIf(int* arr, int size, function <bool(int)> f) {
    int count = 0;

    for(int i = 0; i < size; i++) {
        if(f(arr[i])) {
            count++;
        }
    }

    return count;
}

bool allMatch(int* arr, int size, function <bool(int)> predicat) {
    for(int i = 0; i < size; i++) {
        if(!predicat(arr[i])) {
            return false;
        }
    }

    return true;
}

bool anyMatch(int* arr, int size, function <bool(int)> predicate) {
    for(int i = 0; i < size; i++) {
        if(predicate(arr[i])) {
            return true;
        }
    }

    return false;
}

int maxBy(int* arr, int size, function <int(int)> predicate) {
    int max = predicate(arr[0]);
    int current = arr[0];

    for(int i = 1; i < size; i++) {
        if(max < predicate(arr[i])) {
            max = predicate(arr[i]);
            current = arr[i];
        }
    }

    return current;
}

function <int(int)> compose(function <int(int)> f, function <int(int)> g) {
    return [f, g](int x) {return f(g(x)); };
}

int applyNTimes(function <int(int)> f, int x, int n) {
    for(int i = 0; i < n; i++) {
        x = f(x);
    }

    return x;
}

void bubbleSort(int* arr, int size, function <bool(int, int)> comparator) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(comparator(arr[j], arr[j+1])) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

function <int(int)> makeMultiplier(int n) {
    return [n](int x) {return x*n; };
}

int main() {
    int* arr = new int[6]{1, 2, 3, 4, 5, 6};
    int counter = countIf(arr, 6, [](int a) {return a % 2 == 0; });

    cout << counter << endl;

    delete[] arr;

    return 0;
}