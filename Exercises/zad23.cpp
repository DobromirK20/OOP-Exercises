#include <iostream>
#include <fstream>
using namespace std;

void writeStudents() {
    ofstream file("students.txt");
    if(!file) return;

    file << "Ivan" << " " << 5.50 << endl;
    file << "Mariq" << " " << 6.00 << endl;
    file << "Petur" << " " << 4.75 << endl;
}

void readStudents() {
    ifstream file("students.txt");
    if(!file) return;

    char name[100];
    double grade;

    while(file >> name >> grade) {
        cout << name << ": " << grade << endl;
    }
}

void readLines() {
    ifstream file("notes.txt");
    if(!file) return;

    char line[256];
    int lineNum = 1;

    while (file.getline(line, 256))
    {
        cout << lineNum++ << ": " << line << endl;
    }
    
}

int main() {
    return 0;
}