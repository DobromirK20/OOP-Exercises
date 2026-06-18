#include <iostream>
#include <cstring>
using namespace std;

class Product
{
private:
    unsigned int id;
    char* name;
    double weight;
    bool isBreakable;

    void copyFrom(const Product& other) {
        id = other.id;
        weight = other.weight;
        isBreakable = other.isBreakable;

        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }

    void free() {
        delete[] name;
    }

public:
    Product(unsigned int i, const char* n, double w, bool ib) : id(i), weight(w), isBreakable(ib){
        if(validateName(n)) {
            name = new char[strlen(n) + 1];
            strcpy(name, n);
        }
        else {
            name = new char[8];
            strcpy(name, "Default");
        }   
    }

    Product(const Product& other) {
        copyFrom(other);
    }

    Product& operator=(const Product& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    ~Product() {
        free();
    }

    unsigned int getID() const {
        return id;
    }

    const char* getName() const {
        return name;
    }

    double getWeight() const {
        return weight;
    }

    bool getIsBreakable() const {
        return isBreakable;
    }

    bool operator<(const Product& other) const {
        return (id < other.id) ? true : false; 
    }

    void print() const {
        cout << id << endl;
        cout << name << endl;
        cout << weight << endl;
        cout << isBreakable << endl;
    }

    void updateName(const char* other) {
        if(!validateName(other)) return;

        int len = strlen(other);
        delete[] name;
        name = new char[len + 1];
        strcpy(name,other);
    }
    
    bool check(double other) const {
        return (weight >= other) ? true : false;
    }

    static bool validateName(const char* n) {
        if(n == nullptr) return false;

        if(strlen(n) > 0 && strlen(n) <= 80) {
            return true;
        }
        else {
            cout << "Nevalidniq etiket ne promenq sustoqnieto na teksta" << endl;
            return false;
        }
    }

    bool operator==(const Product& other) const {
        return id == other.id;
    }

    char* shortRepresenation() const {
    char* result = new char[50];

    result[0] = 'S';
    result[1] = 'K';
    result[2] = 'U';
    result[3] = '[';

    unsigned int temp = id;
    char digits[20];
    int len = 0;

    if(temp == 0) {
        digits[len++] = '0';
    }
    else {
        while(temp > 0) {
            digits[len++] = (temp % 10) + '0';
            temp /= 10;
        }
    }

    int index = 4;
    for(int i = len - 1; i >= 0; i--) {
        result[index++] = digits[i];
    }

    result[index++] = ']';
    result[index] = '\0';

    return result;
    }

    double totalWeight(unsigned int quantity) const {
        return weight * quantity;
    }
};

int main() {
    return 0;
}