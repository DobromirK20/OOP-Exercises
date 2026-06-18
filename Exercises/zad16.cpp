#include <iostream>
#include <cstring>
using namespace std;

class Book
{
private:
    char* title;
    char* author;
    int year;
    char* isbn;

public:
    //Book() : title(nullptr), author(nullptr), year(0), isbn(nullptr) {}

    Book() { //tova uj e po-bezopasno
       title = new char[1];
       title[0] = '\0';

       author = new char[1];
       author[0] = '\0';

       isbn = new char[1];
       isbn[0] = '\0';

       year = 0;
    }

    Book(const char* t, const char* a, int y, const char* i) {
        title = new char[strlen(t) + 1];
        strcpy(title, t);

        author = new char[strlen(a) + 1];
        strcpy(author, a);

        year = y;

        isbn = new char[strlen(i) + 1];
        strcpy(isbn, i);
    }

    Book(const Book& other) {
        title = new char[strlen(other.title) + 1];
        strcpy(title, other.title);

        author = new char[strlen(other.author) + 1];
        strcpy(author, other.author);

        year = other.year;

        isbn = new char[strlen(other.isbn) + 1];
        strcpy(isbn, other.isbn);
    }

    Book& operator=(const Book& other) {
        if(this != &other) {
            delete[] title;
            delete[] author;
            delete[] isbn;

            title = new char[strlen(other.title) + 1];
            strcpy(title, other.title);

            author = new char[strlen(other.author) + 1];
            strcpy(author, other.author);

            year = other.year;

            isbn = new char[strlen(other.isbn) + 1];
            strcpy(isbn, other.isbn);
        }

        return *this;
    }

    const char* getIsbn() const {
        return isbn;
    }

    const char* getAuthor() const {
        return author;
    }

    void print() const {
        cout << title << " | " << author << " | " << year << " | " << isbn << endl;
    }

    ~Book() {
        delete[] title;
        delete[] author;
        delete[] isbn;
    }
    
};

class Library
{
private:
    Book* books;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        Book* newBooks = new Book[capacity];

        for(int i = 0;i < size; i++) {
            newBooks[i] = books[i];
        }

        delete[] books;
        books = newBooks;
    }

    void copyFrom(const Library& other) { 
        size = other.size;
        capacity = other.capacity;

        books = new Book[capacity];

        for(int i = 0; i < size; i++) {
            books[i] = other.books[i];
        }
    }

    void free() {
        delete[] books;
    }

public:
    Library() : size(0), capacity(4) {
        books = new Book[capacity];
    }

    Library(const Library& other) {
        copyFrom(other);
    }

    Library& operator=(const Library& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }

        return *this;
    }

    ~Library() {
        free();
    }

    void addBook(const Book& x) {
        if(size >= capacity) {
            resize();
        }

        books[size++] = x;
    }

    void removeBook(const char* isbn) {
        for(int i = 0; i < size; i++) {
            if(strcmp(isbn, books[i].getIsbn()) == 0) {
                for(int j = i; j < size - 1; j++) {
                    books[j] = books[j + 1];
                }
                size--;
                return;
            }
        }
    }

    void findByAuthor(const char* author) {
        for(int i = 0; i < size; i++) {
            if(strcmp(author, books[i].getAuthor()) == 0) {
                books[i].print();
            }
        }
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            books[i].print();
        }
    }
};

int main() {
    Library lib;

    Book b1("C++ Basics", "Ivan", 2020, "111");
    Book b2("OOP", "Ivan", 2021, "222");
    Book b3("Math", "Petar", 2019, "333");

    lib.addBook(b1);
    lib.addBook(b2);
    lib.addBook(b3);

    cout << "All books:" << endl;
    lib.print();

    cout << "\nBooks by Ivan:" << endl;
    lib.findByAuthor("Ivan");

    cout << "\nRemoving ISBN 222..." << endl;
    lib.removeBook("222");

    lib.print();

    return 0;
}



