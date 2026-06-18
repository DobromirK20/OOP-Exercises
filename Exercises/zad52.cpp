#include <iostream>
#include <cstring>
using namespace std;

class Media
{
public:
    virtual void play() const = 0;
    virtual void getInfo() const = 0;
    virtual double getDuration() const = 0;
    virtual Media* clone() const = 0;
    virtual ~Media() {}
};

class Song : public Media
{
private:
    char* title;
    char* artist;
    double duration;

    void copy(const Song& other) {
        duration = other.duration;
        title = new char[strlen(other.title) + 1];
        strcpy(title, other.title);
        artist = new char[strlen(other.artist) + 1];
        strcpy(artist, other.artist);
    }

    void free() {
        delete[] title;
        delete[] artist;
    }
public:
    Song(const char* t = "", const char* a = "", double d = 0) : duration(d) {
        title = new char[strlen(t) + 1];
        strcpy(title, t);
        artist = new char[strlen(a) + 1];
        strcpy(artist, a);
    }

    Song(const Song& other) {
        copy(other);
    }

    Song& operator=(const Song& other) {
        if(this != &other) {
            free();
            copy(other);
        }

        return *this;
    }

    void play() const override {
        cout << "Play: " << title << endl;
    }

    void getInfo() const override {
        cout << "Title: " << title << endl;
        cout << "Artist: " << artist << endl;
        cout << "Duration: " << duration << endl;
    }

    double getDuration() const override {
        return duration;
    }

    Media* clone() const override {
        return new Song(*this);
    }

    ~Song() override {
        free();
    }
};

class Podcast : public Media
{
private:
    char* title;
    char* podcaster;
    int countPodcasts;
    double averageLenght;

    void copy(const Podcast& other) {
        title = new char[strlen(other.title) + 1];
        strcpy(title, other.title);
        podcaster = new char[strlen(other.podcaster) + 1];
        strcpy(podcaster, other.podcaster);
        countPodcasts = other.countPodcasts;
        averageLenght = other.averageLenght;
    }

    void free() {
        delete[] title;
        delete[] podcaster;
    }
public:
    Podcast(const char* t = "", const char* p = "", int cp = 0, double al = 0) : countPodcasts(cp), averageLenght(al) {
        title = new char[strlen(t) + 1];
        strcpy(title, t);
        podcaster = new char[strlen(p) + 1];
        strcpy(podcaster, p);
    }

    Podcast(const Podcast& other) {
        copy(other);
    }

    Podcast& operator=(const Podcast& other) {
        if(this != &other) {
            free();
            copy(other);
        }

        return *this;
    }

    void play() const override {
        cout << "Play: " << title << endl;
    }

    void getInfo() const override {
        cout << "Title: " << title << endl;
        cout << "Podcaster: " << podcaster << endl;
        cout << "Count podcasts: " << countPodcasts << endl;
        cout << "Average lenght: " << averageLenght << endl; 
    }

    double getDuration() const override {
        return averageLenght * countPodcasts;
    }

    Media* clone() const override {
        return new Podcast(*this);
    }

    ~Podcast() override {
        free();
    }
};

class Audiobook : public Media {
private:
    char* title;
    char* author;
    double duration;
    int currentPosition;

    void copyFrom(const Audiobook& other) {
        title = new char[strlen(other.title) + 1];
        strcpy(title, other.title);
        author = new char[strlen(other.author) + 1];
        strcpy(author, other.author);
        duration = other.duration;
        currentPosition = other.currentPosition;
    }

    void free() {
        delete[] title;
        delete[] author;
    }

public:
    Audiobook(const char* title = "",
              const char* author = "",
              int duration = 0,
              int currentPosition = 0) {

        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);

        this->author = new char[strlen(author) + 1];
        strcpy(this->author, author);

        this->duration = duration;
        this->currentPosition = currentPosition;
    }

    Audiobook(const Audiobook& other) {
        copyFrom(other);
    }

    Audiobook& operator=(const Audiobook& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }

        return *this;
    }

    ~Audiobook() {
        free();
    }

    void play() const override {
        cout << "Playing audiobook: "
             << title
             << " from minute "
             << currentPosition
             << endl;
    }

    void getInfo() const override {
        cout << "Audiobook: "
             << title
             << ", Author: "
             << author
             << ", Duration: "
             << duration
             << ", Current position: "
             << currentPosition
             << endl;
    }

    double getDuration() const override {
        return duration;
    }

    Media* clone() const override {
        return new Audiobook(*this);
    }
};

class Playlist
{
private:
    Media** media;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        Media** newMedia = new Media*[capacity];
        for(int i = 0; i < size; i++) {
            newMedia[i] = media[i];
        }
        delete[] media;
        media = newMedia;
    }

    void copy(const Playlist& other) {
        size = other.size;
        capacity = other.capacity;
        media = new Media*[capacity];
        for(int i = 0; i < size; i++) {
            media[i] = other.media[i]->clone();
        }
    } 

    void free() {
        for(int i = 0; i < size; i++) {
            delete media[i];
        }
        delete[] media;
    }
public:
    Playlist(int s = 0, int c = 2) : size(s), capacity(c) {
        media = new Media*[capacity];
    }

    Playlist(const Playlist& other) {
        copy(other);
    }

    Playlist& operator=(const Playlist& other) {
        if(this != &other) {
            free();
            copy(other);
        }

        return *this;
    }

    void addMedia(const Media& m) {
        if(size == capacity) {
            resize();
        }

        media[size++] = m.clone();
    }

    void removeMedia(Media* m) {
        if(size > 0) {
            int index = 0;

            while (index < size && media[index] != m)
            {
                index++;
            }

            if(index == size) {
                return;
            }

            delete media[index];
            
            for(int i = index; i < size - 1; i++) {
                media[i] = media[i + 1];
            }

            size--;
        }
    }

    void playAll() const {
        for(int i = 0; i < size; i++) {
            media[i]->play();
        }
    }

    void printInfo() const {
        for (int i = 0; i < size; i++) {
            media[i]->getInfo();
        }
    }

    double getTotalDuration() const {
        double total = 0;

        for (int i = 0; i < size; i++) {
            total += media[i]->getDuration();
        }

        return total;
    }

    ~Playlist() {
        free();
    }
};

int main() {
    Song s("Shape of You", "Ed Sheeran", 4);
    Podcast p("Tech Talk", "Ivan", 10, 30);
    Audiobook a("Harry Potter", "J. K. Rowling", 500, 120);

    Playlist playlist;

    playlist.addMedia(s);
    playlist.addMedia(p);
    playlist.addMedia(a);

    playlist.printInfo();

    cout << endl;
    playlist.playAll();

    cout << endl;
    cout << "Total duration: "
         << playlist.getTotalDuration()
         << endl;

    Playlist copy = playlist;

    cout << endl;
    cout << "Copied playlist:" << endl;
    copy.printInfo();

    return 0;
}


