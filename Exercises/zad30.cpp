#include  <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Student
{
private:
    char* name;
    int facultyNumber;
    double* grades;
    int gradesCount;

    void copyFrom(const Student& other) {
        facultyNumber = other.facultyNumber;

        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);

        gradesCount = other.gradesCount;
        if(grades > 0) {
           grades = new double[gradesCount];
           for(int i = 0; i < gradesCount; i++) {
               grades[i] = other.grades[i];
           }
        }
        else { 
            grades = nullptr;
        }
    }

    void free() {
        delete[] name;
        delete[] grades;
        name = nullptr;
        facultyNumber = 0;
        grades = nullptr;
        gradesCount = 0;
            
    }
public:
    Student() : name(nullptr), facultyNumber(0), gradesCount(0), grades(nullptr) {}

    Student(const char* n, int fn, const double* g, int gc) {        
        name = new char[strlen(n) + 1];
        strcpy(name, n);

        facultyNumber = fn;
         
        if(gc > 0) {
            gradesCount = gc;
            grades = new double[gradesCount];
            for(int i = 0; i < gradesCount; i++) {
                grades[i] = g[i];
            }
        }
        else {
            gc = 0;
            grades = nullptr;
        }
    }

    Student(const Student& other) {
        copyFrom(other);
    }

    Student& operator=(const Student& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }

        return *this;
    }

    ~Student() {
        free();
    }

    int getFacultyNumber() const {
        return facultyNumber;
    }

    const double* getGrades() const {
        return grades;
    }

    int getGradesCount() const {
        return gradesCount;
    }

    const char* getName() const {
        return name;
    }

    friend ostream& operator<<(ostream& os, const Student& s);
};

ostream& operator<<(ostream& os, const Student& s) {
    os << "Ime: " << s.name << endl;
    os << "Fakulteten nomer: " << s.facultyNumber << endl;
    os << "Ocenki: ";

    if (s.gradesCount == 0) {
        os << "nyama";
    } 
    else {
        for (int i = 0; i < s.gradesCount; i++) {
            os << s.grades[i];
            if (i < s.gradesCount - 1) {
                os << ", ";
            }
        }
    }

    os << endl;

    return os;
}


class StudentDatabase
{
private:
    Student* students;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        Student* newStudents = new Student[capacity];

        for(int i = 0; i < size; i++) {
            newStudents[i] = students[i];
        }

        delete[] students;
        students = newStudents;
    }

    void copyFrom(const StudentDatabase& other) {
        capacity = other.capacity;
        size = (other.size < other.capacity) ? other.size : other.capacity;

        students = new Student[capacity];
        for(int i = 0; i < size; i++) {
            students[i] = other.students[i];
        }
    }

    void free() {
        delete[] students;
        students = nullptr;
        size = 0;
        capacity = 4;
    }
public:
    StudentDatabase() : size(0), capacity(4) {
        students = new Student[capacity];
    }

    StudentDatabase(const Student* st, int s, int c) {
        capacity = c;
        size = (s > c) ? c : s;

        students = new Student[capacity];

        for(int i = 0; i < size; i++) {
            students[i] = st[i];
        }
    }

    StudentDatabase(const StudentDatabase& other) {
        copyFrom(other);
    }

    StudentDatabase& operator=(const StudentDatabase& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }

        return *this;
    }

    ~StudentDatabase() {
        free();
    }

    void add(const Student& s) {
        if(size >= capacity) {
            resize();
        }

        students[size++] = s;
    }

    bool removeByFN(int fn) {
        if(size == 0) return false;

        int index = -1;

        for(int i = 0; i < size; i++) {
            if(students[i].getFacultyNumber() == fn) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            return false;
        }

        for(int i = index; i < size - 1; i++) {
            students[i] = students[i+1];
        }

        size--;
        return true;
    }

    Student findByFN(int fn) const {
        if(size == 0) return;

        int index = -1;

        for(int i = 0; i < size; i++) {
            if(students[i].getFacultyNumber() == fn) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            return;
        }

        return students[index];
    }

    double averageGrade(const Student& s) const {
        if (s.getGradesCount() == 0) {
            return 0.0;
        }

        double sum = 0;

        for(int i = 0; i < s.getGradesCount(); i++) {
            sum += s.getGrades()[i];
        }

        return sum / s.getGradesCount();
    }

    void saveToTextFile(const char* filename) const {
        ofstream out(filename, ios::binary);
        if(!out) {
            cout << "Greshka pri zapis vuv fail";
            return;
        }

        //out << size << endl;
        out.write((const char*)&size, sizeof(size));

        for(int i = 0; i < size; i++) {
            int nameLen = strlen(students[i].getName());
            out.write((const char*)&nameLen, sizeof(nameLen));
            out.write(students[i].getName(), nameLen);
            //out << students[i].getName() << endl;
            //out << students[i].getFacultyNumber() << endl;
            //out << students[i].getGradesCount() << endl;

            int fn = students[i].getFacultyNumber();
            out.write((const char*)&fn, sizeof(fn));

            int gradesCount = students[i].getGradesCount();
            out.write((const char*)&gradesCount, sizeof(gradesCount));


            for(int j = 0; j < gradesCount; j++) {
                //out << students[i].getGrades()[j] << " ";
                double grade = students[i].getGrades()[j];
                out.write((const char*)&grade, sizeof(grade));
            }
            //out << endl;
        }

        out.close();
    }

    void loadFromTextFile(const char* filename) {
        ifstream in(filename);
        if(!in) {
            cout << "Greshka pri chetene ot fail!" << endl;
            return;
        }

        free();
        capacity = 4;
        size = 0;
        students = new Student[capacity];

        int count;
        if (!(in >> count)) {
            cout << "Nevaliden format!" << endl;
            return;
        }

        in.ignore();

        for(int i = 0; i < count; i++) {
            char name[1024];
            in.getline(name,1024);

            int fn;
            in >> fn;

            int gradesCount;
            in >> gradesCount;

            double* grades = nullptr;
            if(gradesCount > 0) {
                grades = new double[gradesCount];
                for(int j = 0; j < gradesCount; j++) {
                    in >> grades[j];
                }
            }

            in.ignore();

            Student s(name, fn, grades, gradesCount);
            add(s);

            delete[] grades;
        }

        in.close();
    }

    friend ostream& operator<<(ostream& os, const StudentDatabase& db);
};

ostream& operator<<(ostream& os, const StudentDatabase& db) {
    os << "===== STUDENT DATABASE =====" << endl;
    os << "Broi studenti: " << db.size << endl;
    os << endl;

    for (int i = 0; i < db.size; i++) {
        os << "Student #" << i + 1 << endl;
        os << db.students[i] << endl;
    }

    return os;
}




