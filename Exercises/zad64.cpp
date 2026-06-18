#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum Types {TEXT_DOCUMENT, FOLDER};

class Node
{
protected:
    string name;
    Types types;
public:
    Node(const string& n, Types t) : name(n), types(t) {}
    virtual void ListContents() const = 0;
    virtual Node* copy() const = 0;
    virtual ~Node(){}
};

class TextDocument : public Node
{
private:
    string informationStored;
public:
    TextDocument(const string& i, const string& n) : informationStored(i), Node(n,TEXT_DOCUMENT) {}

    void ListContents() const override {
        cout << "Text document: " << name << endl;
        cout << informationStored << endl;
    }

    Node* copy() const override {
        return new TextDocument(*this);
    }
};

class Folder : public Node
{
private:
    vector<Node*> contents;
public:
    Folder(const string& n) : Node(n,FOLDER){}

    Folder(const Folder& other) : Node(other.name,other.types) {
        for(Node* c : other.contents) {
            contents.push_back(c->copy());
        }
    }

    Folder& operator=(const Folder& other) {
        if(this != &other) {
            for(Node* c : contents) {
                delete c;
            }

            contents.clear();

            name = other.name;
            types = other.types;

            for(Node* c : other.contents) {
                contents.push_back(c->copy());
            }
        }

        return *this;
    }

    void add(Node* element) {
        contents.push_back(element->copy());
    }

    void ListContents() const override {
        cout << "Folder: " << name << endl;
        for(size_t i = 0; i < contents.size(); i++) {
            contents[i]->ListContents();
        }
    }

    Node* copy() const override {
        return new Folder(*this);
    }

    ~Folder() {
        for(Node* c : contents) {
            delete c;
        }
    }
};

int main()
{
    Folder data("Data");

    TextDocument act("Act information", "Act");

    Folder employees("Employees");

    TextDocument maria("Employee Maria", "Maria");
    TextDocument ivanka("Employee Ivanka", "Ivanka");

    employees.add(&maria);
    employees.add(&ivanka);

    Folder departments("Departments");

    TextDocument manufacturing(
        "Manufacturing department",
        "Manufacturing"
    );

    departments.add(&manufacturing);

    data.add(&act);
    data.add(&employees);
    data.add(&departments);

    data.ListContents();

    return 0;
}
