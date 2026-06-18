#include <iostream>
using namespace std;

struct Address
{
    char city[50];
    char street[100];
    int number;
};

struct Student
{
    char name[100];
    int facultyNumber;
    double averageGrade;
    Address address;
};

void printStudentCard(const Student& s) {
    cout << s.name << endl;
    cout << s.facultyNumber << endl;
    cout << s.averageGrade << endl;
    cout << s.address.city << endl;
    cout << s.address.street << endl;
    cout << s.address.number << endl;
}

int main()
{
    Student s1 =
    {
        "Ivan Petrov",
        12345,
        5.67,
        { "Sofia", "Tsar Osvoboditel", 15 }
    };

    printStudentCard(s1);

    return 0;
}