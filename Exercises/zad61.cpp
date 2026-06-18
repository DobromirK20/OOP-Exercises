#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Box
{
private:
    T data;
public:
    Box(const T& data) {
        this->data = data;
    }

    void set(const T& data) {
        this->data = data;
    }

    T get() const {
        return data;
    }
};

template <>
class Box<string>
{
private:
    string data;
    int words;
public:
    Box(const string& data) {
        set(data);
    }

    void set(const string& data) {
        this->data = data;

        words = 0;
        bool inWord = true;

        for(char c : data) {
            if(c != ' ') {
                if(!inWord) {
                    words++;
                    inWord = true;
                }
            }
            else {
                inWord = false;
            }
        }
    }

    string get() const {
        return data;
    }

    int getWordCount() const {
        return words;
    }
};

int main() {
    Box<int> b1(10);
    cout << b1.get() << endl;

    b1.set(25);
    cout << b1.get() << endl;

    Box<string> b2("Hello world from C++");

    cout << b2.get() << endl;
    cout << b2.getWordCount() << endl;

    b2.set("One two three four five");
    cout << b2.getWordCount() << endl;

    return 0;
}
