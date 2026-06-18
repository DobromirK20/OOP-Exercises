#include <iostream>
#include <cstring>

class Professor
{
    char name[100];
    char field[50];
public:
    Professor(const char* n = "", const char* f = "") {
        strncpy(name,n,99);
        name[99] = '\0';
        strncpy(field,f,49);
        field[49] = '\0';
    }
    
    const char* getName() const {
        return name;
    }

    const char* getField() const {
        return field;
    }
};

class Department
{
    char name[50];
    Professor professors[20];
    int profCount;
public:
    Department(const char* n ="") : profCount(0) {
        strncpy(name, n , 49);
        name[49] = '\0';
    }

    void addProfessor(const Professor& p) {
        if(profCount < 20) {
            professors[profCount++] = p;
        }
    }

    const char* getName() const {
        return name;
    }

    int getProfCount() const {
        return profCount;
    }

    void print() const {
        std::cout << "  Катедра: " << name << " (" << profCount << " преподаватели)" << std::endl;
        for (int i = 0; i < profCount; i++) {
            std::cout << "    - " << professors[i].getName() 
                      << " (" << professors[i].getField() << ")" << std::endl;
        }
    }
};

class University {
    char name[100];
    Department departments[10];
    int deptCount;
public:
    University(const char* n) : deptCount(0) {
        strncpy(name, n, 99);
        name[99] = '\0'; 
    }

    void addDepartment(const Department& d) {
        if(deptCount < 10) {
            departments[deptCount++] = d;
        }
    }

    void print() const {
        std::cout << "Университет: " << name << std::endl;
        for (int i = 0; i < deptCount; i++) {
            departments[i].print();
        }
    }
};

int main() {
    University uni("Софийски университет");
    
    Department cs("Компютърни науки");
    cs.addProfessor(Professor("Проф. Иванов", "Алгоритми"));
    cs.addProfessor(Professor("Проф. Петрова", "ИИ"));
    
    Department math("Математика");
    math.addProfessor(Professor("Проф. Георгиев", "Анализ"));
    
    uni.addDepartment(cs);
    uni.addDepartment(math);
    uni.print();
    
    return 0;
}