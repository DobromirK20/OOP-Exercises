#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

void reverse() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    if(!in || !out) return;

    int capacity = 2;

    char** lines = new char*[capacity];
    char* buffer = new char[256];
    int count = 0;

    while(in.getline(buffer, 256)) {
        if(count == capacity) {
            int newCapacity = capacity * 2;

            char** newLines = new char*[newCapacity];

            for(int i = 0; i < count; i++) {
                newLines[i] = lines[i];
            }

            delete[] lines;
            lines = newLines;
            capacity = newCapacity;
        }

        lines[count] = new char[strlen(buffer) + 1];
        strcpy(lines[count], buffer);
        count++; 
    }

    for(int i = count - 1; i >= 0; i--) {
        out << lines[i] << endl;
    }

    for(int i = 0; i < count; i++) {
        delete[] lines[i];
    }

    delete[] buffer;
    delete[] lines;
}

void longest() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    if(!in || !out) return;

    int capacity = 2;
    char** lines = new char*[capacity];
    int count = 0;
    char* buffer = new char[256];

    while(in.getline(buffer,256)) {
        if(count == capacity) {
            capacity *= 2;
            char** newData = new char*[capacity];

            for(int i = 0; i < count; i++) {
                newData[i] = lines[i];
            }

            delete[] lines;
            lines = newData;
        }

        lines[count] = new char[strlen(buffer) + 1];
        strcpy(lines[count], buffer);
        count++;
    }

    int lenght = 0;
    char* temp = nullptr;

    for(int i = 0; i < count; i++) {
        if(lenght < strlen(lines[i])) {
            temp = lines[i];
            lenght = strlen(lines[i]);
        }
    }

    if(temp != nullptr) {
        out << temp << endl;
    }

    for(int i = 0; i < count; i++) {
        delete[] lines[i];
    }

    delete[] buffer;
    delete[] lines;
}

double parseDouble(const char* str) {
    double result = 0;
    double fraction = 0;
    double divisor = 1;
    bool afterDot = false;

    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '.') {
            afterDot = true;
        }
        else if(str[i] >= '0' && str[i] <= '9') {
            if(!afterDot) {
                result = result * 10 + (str[i] - '0');
            } else {
                fraction = fraction * 10 + (str[i] - '0');
                divisor *= 10;
            }
        }
    }

    return result + fraction / divisor;
}

void filterStudents() {
    ifstream in("students.txt");
    ofstream out("passed.txt");

    if(!in || !out) return;

    int capacity = 2;
    char** lines = new char*[capacity];
    int count = 0;
    char* buffer = new char[256];

    while(in.getline(buffer,256)) {
        if(count == capacity) {
            capacity *= 2;
            char** newLines = new char*[capacity];
            
            for(int i = 0; i < count; i++) {
                newLines[i] = lines[i];
            }

            delete[] lines;
            lines = newLines;
        }

        lines[count] = new char[strlen(buffer) + 1];
        strcpy(lines[count],buffer);
        count++;
    }

    char* name = new char[100];
    double grade = 0;

    for(int i = 0; i < count; i++) {
        int j = 0;

        while(lines[i][j] != ' ' && lines[i][j] != '\0') {
            name[j] = lines[i][j];
            j++;
        }
        name[j] = '\0';

        j++;

        grade = parseDouble(&lines[i][j]);

        if(grade >= 4.00) {
            out << name << " " << grade << endl;
        }
    }

    for(int i = 0; i < count; i++) {
        delete[] lines[i];
    }

    delete[] lines;
    delete[] buffer;
    delete[] name;
}

void filterStudents2() {
    ifstream in("students.txt");
    ofstream out("passed.txt");

    if(!in || !out) return;

    char* name = new char[100];
    double grade = 0.0;

    while (in >> name >> grade)
    {
        if(grade >= 4.00) {
           out << name << " " << grade << endl;
        }
    }

    delete[] name;
}

int main() {
    return 0;
}