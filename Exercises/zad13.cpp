#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* data;
    int length;

    void copyFrom(const String& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    void free() {
        delete[] data;
        data = nullptr;
        length = 0;
    }

public:
    String(const char* str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data,str);
        cout << "  [Конструктор] \"" << data << "\"" << endl;
    }

    String(const String& other) {
        copyFrom(other);
        cout << "  [Copy ctor] \"" << data << "\"" << endl;
    }

    String& operator=(const String& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }

        cout << "  [operator=] \"" << data << "\"" << endl;

        return *this;
    }

    const char* c_str() const {
        return data;
    }

    int getLength() const {
        return length;
    }

    ~String() {
        cout << "  [Деструктор] \"" << (data ? data : "null") << "\"" << endl;
        free();
    }
};

int main() {
    cout << "--- Създаване ---" << endl;
    String a("Hello");         
    
    cout << "--- Копиране ---" << endl;
    String b = a;              
    
    cout << "--- Присвояване ---" << endl;
    String c("World");         
    c = a;                     
    
    cout << "--- Край на main ---" << endl;

    return 0;
}
