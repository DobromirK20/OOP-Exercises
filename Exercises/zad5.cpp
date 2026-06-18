#include <iostream>
#include <functional>
using namespace std;

template <typename T>
void mySwap(T& a, T& b) { 
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
T findMin(const T arr[], int size) {
    T min = arr[0];

    for(int i = 1; i < size; i++) {
        if(min > arr[i]) {
            min = arr[i];
        }
    }

    return min;
}

template <typename T>
void sortArray(T arr[], int size, bool (*compare)(const T&, const T&)) {
    for(int i=0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(compare(arr[j], arr[i])) {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

bool ascending(const int& a, const int& b) {
    return a < b;
}


bool descending(const int& a, const int& b) {
    return a > b;
}

int strLen2(const char arr[]) {
    int i = 0;

    while(arr[i] != '\0') {
        i++;
    }

    return i;
}

bool shorterString(const char* const& a, const char* const& b) {
    return strLen2(a) < strLen2(b);
}

template <typename T>
void printArray(const T* arr, int size) {
    for(int i=0; i<size; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

template <typename T>
void forEach(T arr[], int size, std::function<void(T&)> action) {
    for(int i = 0; i < size; i++) {
        action(arr[i]);
    }
}

int main()
{
    int arr1[] = {5, 2, 8, 1, 4};
    int arr2[] = {5, 2, 8, 1, 4};
    const char* words[] = {"apple", "hi", "programming", "car", "sun"};

    sortArray(arr1, 5, ascending);
    cout << "Ascending: ";
    printArray(arr1, 5);

    sortArray(arr2, 5, descending);
    cout << "Descending: ";
    printArray(arr2, 5);

    sortArray(words, 5, shorterString);
    cout << "By length: ";
    printArray(words, 5);

    return 0;
}