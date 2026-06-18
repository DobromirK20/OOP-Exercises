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

    String operator+(const String& other) const {
        int maxLength = length + other.length;
        char* result = new char[maxLength + 1];

        int i = 0, j = 0;

        while(i < length) {
            result[i] = data[i];
            i++;
        }

        while(j != other.length) {
            result[i] = other.data[j];
            i++;
            j++;
        }

        result[maxLength] = '\0';

        String newData(result);
        delete[] result;
 
        return newData;
    }

    String& operator+=(const String& other) {
        int size = length + other.length;
        char* newData = new char[size + 1];

        for(int i = 0; i < length; i++) {
            newData[i] = data[i];
        }

        int j = 0;

        for(int i = length; i < size; i++) {
            newData[i] = other.data[j];
            j++;
        }

        newData[size] = '\0';

        delete[] data;
        data = newData;
        length = size;

        return *this;
    }

    char& operator[](int index) {
        return data[index];
    }

    const char& operator[](int index) const {
        return data[index];
    }

    bool operator==(const String& other) const {
        if(length != other.length) return false;

        for(int i = 0; i < length; i++) {
            if(data[i] != other.data[i]) return false;
        }

        return true;
    }

    bool operator<(const String& other) const {
        int minLength = (length < other.length) ? length : other.length;

        for(int i = 0; i < minLength; i++) {
            if(data[i] > other.data[i]) return false;
            if(data[i] < other.data[i]) return true;
        }

        return length < other.length;
    }

    friend ostream& operator<<(ostream& os, const String& s);
    friend istream& operator>>(istream& is, String& s);

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

ostream& operator<<(ostream& os, const String& s) {
    os << s.data;
    return os;
}

istream& operator>>(istream& is, String& s) {
    char buffer[1024];
    is >> buffer;

    delete[] s.data;
    s.data = new char[strlen(buffer) + 1];
    s.length = strlen(buffer);
    for(int i = 0; i < s.length; i++) {
        s.data[i] = buffer[i];
    }
    s.data[s.length] = '\0';

    return is;
}

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
