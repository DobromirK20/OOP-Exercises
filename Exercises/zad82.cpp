#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

class TextTransformer
{
protected:
    string words;
public:
    TextTransformer(const string& w = "") : words(w){}
    virtual void append(const string& word) = 0;
    virtual string getResult() const {
        return words;
    }
    virtual ~TextTransformer() {}
};

class UpperTransformer : public TextTransformer
{
public:
    UpperTransformer(const string& w = "") : TextTransformer(w) {}

    void append(const string& word) override {
        string result = word;

        for(int i = 0; i < word.size(); i++) {
            if(word[i] >= 'a' && word[i] <= 'z'){
                result[i] = word[i] + ('A' - 'a');
            }
        }

        words += result;
    }
};

class FilterTransformer : public TextTransformer
{
private:
    char c;
public:
    FilterTransformer(const string& w, char s) : c(s), TextTransformer(w){}

    void append(const string& word) override {
        if(word.empty()) {
            return;
        }

        if(word[0] == c) {
            if(!words.empty()){
                words += " ";
            }

            words += word;
        }
    }
};

class MapTransformer : public TextTransformer
{
private:
    function <string(string)> func;
public:
    MapTransformer(function <string(string)> f, const string& word) : func(f), TextTransformer(word) {}
    
    void append(const string& word) override {
        words += func(word);
    }
};

string processText(const vector<string>& words, TextTransformer* transformer) {
    for(const string& word: words) {
        transformer->append(word);
    }

    return transformer->getResult();
}
