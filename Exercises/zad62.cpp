#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Person
{
private:
    string name;
    int age;
public:
    Person(const string& n = "", int a = 0) : name(n), age(a) {}

    void serialize(ostream& os) const {
        os << name << endl;
        os << age << endl;
    }
    
    void deserialize(istream& is) {
        getline(is,name);
        is >> age;
        is.ignore();
    }
};

int main() {
    Person p1("Ivan",20);
    Person p2("Stoqn",40);

    ofstream fileOut("person.txt");
    fileOut << "Inked" << endl;
    fileOut << 44 << endl;
    fileOut.close();

    ifstream fileIn("person.txt");

    p1.serialize(cout);
    p1.deserialize(fileIn);
    p1.serialize(cout);

    fileIn.close();

    vector<Person> people;
    people.push_back(p1);
    people.push_back(p2);

    ofstream out("people.txt");

    out << people.size() << endl;

    for(Person p : people) {
        p.serialize(out);
    }

    out.close();

    ifstream in("people.txt");

    size_t count = 0;
    in >> count;
    in.ignore();

    vector<Person> loadedPeople;

    for(size_t i = 0; i < count; i++)
    {
        Person p;
        p.deserialize(in);
        loadedPeople.push_back(p);
    }

    in.close();

    for(Person p : loadedPeople)
    {
        p.serialize(cout);
    }

    return 0;
}