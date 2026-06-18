#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student
{
private:
    string name;
    string FN;
    size_t course;
    vector<double> grades;
protected:
    string university;
    bool status;
public:
    string speciality;

    Student(const string& n, const string& fn, const string& s)
       : name(n), FN(fn), course(1), university("Unknown"), status(true), speciality(s) {}

    void setName(const string& n) {
        name = n; 
    }

    void setFN(const string& fn) {
        FN = fn;
    }

    void setCourse(size_t c) {
        course = c;
    }

    void setGrades(const vector<double>& g) {
        grades = g;
    }

    string getName() const {
        return name;
    }

    string getFacultyNumber() const {
        return FN;
    }

    int getCourse() const {
        return course;
    }

    vector<double> getGrades() const {
        return grades;
    }

    void addGrade(double grade) {
        grades.push_back(grade);
    }

    double calculateAverageGrade() const {
        if(grades.empty()) {
            return 0;
        }
        double result = 0;

        for(double gr : grades) {
            result += gr;
        }

        return result/grades.size();
    }

    virtual void printInfo() const
    {
        cout << "Name: " << name << endl;
        cout << "Faculty number: " << FN << endl;
        cout << "Course: " << course << endl;
        cout << "Specialty: " << speciality << endl;
        cout << "University: " << university << endl;
        cout << "Status: ";

        if (status)
        {
            cout << "Active";
        }
        else
        {
            cout << "Inactive";
        }

        cout << endl;

        cout << "Average grade: "
             << calculateAverageGrade()
             << endl;
    }
};

