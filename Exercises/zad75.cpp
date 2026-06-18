#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>
using namespace std;

class NameList
{
private:
    vector<string> names;
public:
    NameList() noexcept {}

    NameList(const NameList& other) = delete;
    NameList& operator=(const NameList& other) = delete;

    NameList(NameList&& other) noexcept {
        names = move(other.names);
    }

    NameList& operator=(NameList&& other) noexcept {
        if(this != &other) {
            names = move(other.names);
        }

        return *this;
    }

    void addName(const string& name) {
        names.push_back(name);
    }

    void print() const {
        for (int i = 0; i < names.size(); i++) {
            cout << names[i] << endl;
        }
    }

    ~NameList() noexcept {}
};

int main() {
    NameList list1;

    list1.addName("Ivan");
    list1.addName("Maria");

    NameList list2 = move(list1);

    list2.print();

    return 0;
}

