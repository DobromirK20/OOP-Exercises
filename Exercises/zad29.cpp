#include <iostream>
#include <fstream>
using namespace std;

void sortFile(const char* filename) {
    ifstream inFile(filename);
    if(!inFile) {
        cout << "Greshka pri otvarqne za chetene!" << endl;
        return;
    }

    double arr[1000];
    int size = 0;

    while (inFile >> arr[size])
    {
        size++;
    }

    inFile.close();
    
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(arr[i] > arr[j]) {
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    ofstream outFile(filename);
    if(!outFile) {
        cout << "Greshka pri otvarqne za zapis!" << endl;
        return;
    }

    for(int i = 0; i < size; i++) {
        outFile << arr[i] << endl;
    }

    outFile.close();
}

int main() {
    const char* filename = "numbers.txt";
    sortFile(filename);
    cout << "Failut beshe sortiran uspeshno!" << endl;
    
    return 0;
}