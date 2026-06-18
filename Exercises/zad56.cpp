#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    virtual Node* copy() const = 0;
    virtual void print(ostream &os) const = 0;
    virtual ~Node(){}
};

class TextDocument : public Node
{
private:
    string text;
public:
    TextDocument(string t) : text(t){}

    Node* copy() const override {
        return new TextDocument(*this);
    }

    void print(ostream &os) const override {
        os << "Text document: " << text;
    }
};

class Folder : public Node
{
private:
    string name;
    vector<Node*> nodes;
public:
    Folder(string n) : name(n) {}

    void addNode(const Node& n) {
        nodes.push_back(n.copy());
    }

    void print(ostream &os) const override {
        os << "Folder: " << name << endl;

        for(size_t i = 0; i < nodes.size(); i++) {
            nodes[i]->print(os);

            if(i + 1 < nodes.size()) {
                os << ", ";
            }
        }

        os << endl;
    }

    Node* copy() const override {
        Folder* newFolder = new Folder(name);

        for(Node* node : nodes) {
            newFolder->addNode(*node);
        }

        return newFolder;
    }

    ~Folder() {
        for(Node* node : nodes) {
            delete node;
        }
    }
};

int main()
{
    Folder f1("folder1");

    TextDocument t1("oop.txt");
    TextDocument t2("hello.txt");

    f1.addNode(t1);
    f1.addNode(t2);

    Folder f2("folder2");

    TextDocument t3("OOP exam");
    f2.addNode(t3);

    f1.addNode(f2);

    f1.print(cout);

    return 0;
}