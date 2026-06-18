#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>
using namespace std;

class InvalidNameException : public runtime_error
{
public:
    InvalidNameException() : runtime_error("Invalid name") {}
};

class ItemNotFoundException : public runtime_error
{
public:
    ItemNotFoundException() : runtime_error("Item not found") {}
};

void validateName(const string& name)
{
    if(name.empty())
    {
        throw InvalidNameException();
    }

    for(char c : name)
    {
        if(!((c >= 'a' && c <= 'z') || c == ' '))
        {
            throw InvalidNameException();
        }
    }
}

class Item
{
protected:
    string itemName;
    string created;
    string author;
    vector<string> tags;
public:
    Item(const string& n, const string& c, const string& a, const vector<string>& t) : 
            itemName(n), created(c), author(a), tags(t) {
                validateName(n);
            }

    string name() const {
        return itemName;
    }

    virtual int size() const = 0;
    virtual Item* clone() const = 0;
    virtual void exportCSV(ostream& os, const string& container) const = 0;

    static Item* createFromType(const string& type, const string& name, 
                                const string& content, const string& author, const string& created, 
                                const vector<string>& tags);

    virtual ~Item() {}
};

string tagsToString(const vector<string>& tags)
{
    string result;

    for(int i = 0; i < tags.size(); i++)
    {
        result += tags[i];

        if(i != tags.size() - 1)
        {
            result += ",";
        }
    }

    return result;
}

class Article : public Item
{
private:
    string content;
public:
    Article(const string& n, const string& c, const string& a, const vector<string>& t,
             const string& con) : Item(n,c,a,t), content(con) {}

    int size() const override {
        return content.size();        
    }

    Item* clone() const override {
        return new Article(*this);
    }

    friend ostream& operator<<(ostream& os, const Article& article) {
        os << article.itemName << ": ";

        for(int i = 0; i < article.content.size() && i < 50; i++) {
            os << article.content[i];
        }

        return os;
    } 

    void exportCSV(ostream& os, const string& container) const override
    {
       os << container << ","
          << itemName << ","
          << "A" << ","
          << content << ","
          << author << ","
          << created << ","
          << tagsToString(tags)
          << endl;
    }
};

class Category : public Item
{
private:
    vector<Item*> items;
public:
    Category(const string& n, const string& c, const string& a, const vector<string>& t) : Item(n,c,a,t) {}

    void addItem(const Item& item) {
        items.push_back(item.clone());
    }

    int size() const override {
        int result = 0;

        for(Item* i : items) {
            result += i->size();
        }

        return result;
    }

    Item* clone() const override {
        return new Category(*this);
    }

    Category(const Category& other) : Item(other.itemName, other.created, other.author, other.tags) {
        for(Item* i : other.items) {
            items.push_back(i->clone());
        }
    }

    void exportCSV(ostream& os, const string& container) const override
    {
    os << container << ","
       << itemName << ","
       << "C" << ","
       << "" << ","
       << author << ","
       << created << ","
       << tagsToString(tags)
       << endl;

    string newContainer;

    if(container == "/")
    {
        newContainer = "/" + itemName;
    }
    else
    {
        newContainer = container + "/" + itemName;
    }

    for(Item* item : items)
    {
        item->exportCSV(os, newContainer);
    }
    } 

    Category(Category&& other) noexcept : Item(move(other.itemName), move(other.created), move(other.author), move(other.tags)){
        items = move(other.items);
        other.items.clear();
    }

    Category& operator=(const Category& other) {
        if(this != &other) {
            for(Item* i : items) {
                delete i;
            }

            items.clear();

            itemName = other.itemName;
            created = other.created;
            author = other.author;
            tags = other.tags;

            for(Item* i : other.items) {
                items.push_back(i->clone());
            }
        }

        return *this;
    }

    Category& operator=(Category&& other) noexcept {
        if(this != &other) {
            for(Item* i : items) {
                delete i;
            }

            items.clear();

            itemName = move(other.itemName);
            created = move(other.created);
            author = move(other.author);
            tags = move(other.tags);
            items = move(other.items);

            other.items.clear();
        }

        return *this;
    }

    void exportAllCSV(ostream& os) const
    {
       os << "container,name,type,content,author,created,tags" << endl;

       for(Item* item : items)
       {
           item->exportCSV(os, "/");
       }
    }

    // class Iterator
    // {
    // private:
    //     const vector<Item*>* it;
    //     int index;
    // public:
    //     Iterator(const vector<Item*>* v, int i) : it(v), index(i) {}

    //     Item* operator*() const{
    //         return (*it)[index];
    //     }

    //     Iterator& operator++() {
    //         ++index;
    //         return *this;
    //     }

    //     bool operator!=(const Iterator& other) const {
    //         return index != other.index;
    //     }
    // };

    class Iterator
    {
    private:
        vector<Item*>::iterator it;
    public:
        Iterator(const vector<Item*>::iterator& i) : it(i) {}

        Item* operator*() const {
            return *it;
        }

        Iterator& operator++() {
            ++it;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }
    };

    Iterator begin() {
        return Iterator(items.begin());
    }

    Iterator end() {
        return Iterator(items.end());
    }

    template <typename T>
T* findByName(const string& n) const {
    for(Item* i : items) {
        if(i->name() == n) {
            T* result = dynamic_cast<T*>(i);

            if(result == nullptr) {
                throw ItemNotFoundException();
            }

            return result;
        }
    }

    throw ItemNotFoundException();
}

    friend ostream& operator<<(ostream& os, const Category& c) {
        os << c.name() << ": " << c.size();
        return os; 
    }

    class ConstIterator
    {
    private:
        vector<Item*>::const_iterator it;
    public:
        ConstIterator(const vector<Item*>::const_iterator& i) : it(i) {}
        
        const Item* operator*() const {
            return *it;
        }

        ConstIterator& operator++() {
            ++it;
            return *this;
        }

        bool operator!=(const ConstIterator& other) const {
            return it != other.it;
        }
    };

    ConstIterator begin() const {
        return ConstIterator(items.begin());
    }

    ConstIterator end() const {
        return ConstIterator(items.end());
    }

    ~Category() {
        for(Item* i : items) {
            delete i;
        }
    }
};

Item* Item::createFromType(const string& type,
                           const string& name,
                           const string& content,
                           const string& author,
                           const string& created,
                           const vector<string>& tags)
{
    if(type == "A")
    {
        return new Article(name, created, author, tags, content);
    }

    if(type == "C")
    {
        return new Category(name, created, author, tags);
    }

    throw runtime_error("Invalid item type");
}

int main()
{
    try
    {
        vector<string> scienceTags = {"science", "physics"};
        vector<string> articleTags = {"theory", "relativity"};

        Category science(
            "science",
            "2024-01-15",
            "admin",
            scienceTags
        );

        Article relativity(
            "relativity",
            "2024-01-17",
            "einstein",
            articleTags,
            "Space and time are relative. E=mc^2."
        );

        science.addItem(relativity);

        cout << "Category size: "
             << science.size()
             << endl;

        cout << endl;

        cout << relativity << endl;

        cout << endl;

        cout << "Iterator:" << endl;

        for(Item* item : science)
        {
            cout << item->name() << endl;
        }

        cout << endl;

        Article* found =
            science.findByName<Article>("relativity");

        cout << "Found: "
             << found->name()
             << endl;

        cout << endl;

        cout << "CSV export:" << endl;

        science.exportAllCSV(cout);
    }
    catch(const InvalidNameException& e)
    {
        cout << e.what() << endl;
    }
    catch(const ItemNotFoundException& e)
    {
        cout << e.what() << endl;
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}