#include <iostream>
#include <fstream>
using namespace std;

void saveArray(const char* filename, const double arr[], int size) {
    ofstream file(filename, ios::binary);
    if(!file) {
        cout << "Greshka pri otvarqne za zapis!" << endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&size), sizeof(int));
    file.write(reinterpret_cast<const char*>(arr), size * sizeof(double));
}

int loadArray(const char* filename, double arr[], int maxSize) {
    ifstream file(filename, ios::binary);
    if(!file) {
        cout << "Gresha pri otvarqne za chetene!" << endl;
        return 0;
    }

    int size;
    file.read(reinterpret_cast<char*>(&maxSize), sizeof(int));
    if(size > maxSize) size = maxSize;
    file.read(reinterpret_cast<char*>(arr), size * sizeof(double));

    return size;
}

int main() {
    return 0;
}