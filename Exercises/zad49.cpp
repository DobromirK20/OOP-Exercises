#include <iostream>
#include <cstring>
using namespace std;

class EventListener
{
public:
    virtual void onEvent(const char* eventName) = 0;

    virtual ~EventListener() {}
};

class LogListener : public EventListener
{
public:
    void onEvent(const char* eventName) override
    {
        cout << "Event received: " << eventName << endl;
    }
};

class CountListener : public EventListener
{
private:
    int count;

public:
    CountListener(int c = 0) : count(c) {}

    void onEvent(const char* eventName) override
    {
        count++;
        cout << "CountListener received event: " << eventName << endl;
    }

    int getCount() const
    {
        return count;
    }
};


class EventEmitter
{
private: 
    EventListener** listeners;
    int size; 
    int capacity;

     void resize()
    {
        capacity *= 2;
        EventListener** newListeners = new EventListener*[capacity];
        for (int i = 0; i < size; i++) {
            newListeners[i] = listeners[i];
        }
        delete[] listeners;
        listeners = newListeners;
    }
public:
    EventEmitter() : size(0), capacity(2) {
        listeners = new EventListener*[capacity];
    }

    void subscribe(EventListener* listener) {
        if (size == capacity)
        {
            resize();
        }

        listeners[size++] = listener;
    }

    void emit(const char* eventName)
    {
        for (int i = 0; i < size; i++)
        {
            listeners[i]->onEvent(eventName);
        }
    }


    ~EventEmitter() {
        delete[] listeners;
    }
};

int main()
{
    EventEmitter emitter;

    LogListener log;
    CountListener counter;

    emitter.subscribe(&log);
    emitter.subscribe(&counter);

    emitter.emit("click");
    emitter.emit("open");
    emitter.emit("close");

    cout << "Counter received events: " << counter.getCount() << endl;

    return 0;
}