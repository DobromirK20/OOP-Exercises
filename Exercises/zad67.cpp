#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
using namespace std;

class SafeFile
{
private:
    fstream file;
public:
    SafeFile(const string& filename) {
        file.open(filename);
        if(!file.is_open()) {
            throw runtime_error("Cannot open file");
        }
    }

    void write(const string& text) {
        if(!file) {
            throw runtime_error("Write error");
        }

        file << text;
    }

    string readLine() {
        string line;

        if(!getline(file, line)) {
            throw runtime_error("Read error");
        }

        return line;
    }

    ~SafeFile() {
        if(file.is_open()) {
            file.close();
        }
    }
};

int main()
{
    try
    {
        SafeFile file("test.txt");

        file.write("Hello world");
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }
}

