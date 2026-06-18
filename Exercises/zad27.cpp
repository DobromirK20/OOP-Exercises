#include <iostream>
#include <fstream>
using namespace std;

struct Student
{
    char name[50];
    int age;
    double grade;
};

void writeBinary() {
    Student s = {"Ivan", 21, 5.50};

    ofstream file("students.bin", ios::binary);
    if(!file) return;

    file.write(reinterpret_cast<const char*>(&s), sizeof(Student));
}

void readBinary() {
    Student s;

    ifstream file("students.bin", ios::binary);
    if(!file) return;

    file.read(reinterpret_cast<char*>(&s), sizeof(Student));
    cout << s.name << ", " << s.age << ", " << s.grade << endl;
}

void writeArray(const Student students[], int count) {
    ofstream file("all_students.bin", ios::binary);
    if(!file) return;

    file.write(reinterpret_cast<const char*>(&count), sizeof(int));
    file.write(reinterpret_cast<const char*>(students), count * sizeof(Student));
}

int readArray(Student students[], int maxCount) {
    ifstream file("all_students.bin", ios::binary);
    if(!file) return 0;

    int count;
    file.read(reinterpret_cast<char*>(&count), sizeof(int));
    if(count > maxCount) count = maxCount;
    file.read(reinterpret_cast<char*>(students), count * sizeof(Student));

    return count;
}

int main() {
    return 0;
}