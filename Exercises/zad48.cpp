#include <iostream>
#include <cstring>
using namespace std;

class Formatter
{
public:
    virtual void format(const char* text) const = 0;

    virtual ~Formatter() {}
};

class UpperCaseFormatter : public Formatter
{
public:
    void format(const char* text) const override {
        int size = strlen(text);

        for(int i = 0; i < size; i++) {
            if(text[i] >= 'a' && text[i] <= 'z') {
                cout << char(text[i] + ('A' - 'a'));
            }
            else {
                cout << text[i];
            }
        }

        cout << endl;
    }
};

class LowerCaseFormatter : public Formatter
{
public:
    void format(const char* text) const override {
        int size = strlen(text);

        for(int i = 0; i < size; i++) {
            if(text[i] >= 'A' && text[i] <= 'Z') {
                cout << char(text[i] - ('A' - 'a'));
            }
            else {
                cout << text[i];
            }
        }

        cout << endl;
    }
};

class TitleCaseFormatter : public Formatter
{
public:
    void format(const char* text) const override {
        bool isNewWord = true; 

        int size = strlen(text);
        
        for(int i = 0; i < size; i++) {
            char current = text[i];

            if(current ==  ' ') {
                isNewWord = true;
                cout << current;
            }
            else {
                if(isNewWord) {
                    if(current >= 'a' && current <= 'z') {
                        cout << current + ('A' - 'a');
                    }
                    else {
                        cout << current;
                    }

                    isNewWord = false;
                }
                else {
                    cout << current;
                }
            }
        }

        cout << endl;
    }
};


class TextEditor
{
private:
    Formatter* strategy;
public:
    TextEditor(Formatter* f) : strategy(f) {}

    void setStrategy(Formatter* s) {
        strategy = s;
    }

    void displayFormatted(const char* text) const {
        strategy->format(text);
    }
};


int main()
{
    UpperCaseFormatter upper;
    LowerCaseFormatter lower;
    TitleCaseFormatter title;

    TextEditor editor(&upper);

    editor.displayFormatted("hello world");

    editor.setStrategy(&lower);
    editor.displayFormatted("HELLO WORLD");

    editor.setStrategy(&title);
    editor.displayFormatted("hello world from cpp");

    return 0;
}