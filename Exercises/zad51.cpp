#include <iostream>
#include <cstring>
using namespace std;

class StockObserver
{
public:
    virtual void onPriceChange(const char* name, double oldPrice, double newPrice) = 0;

    virtual ~StockObserver() {}
};

class AlertObserver : public StockObserver
{
public:
    void onPriceChange(const char* name, double oldPrice, double newPrice) override {
        if((newPrice > oldPrice && (newPrice - oldPrice) > oldPrice / 20) || 
            newPrice < oldPrice && (oldPrice - newPrice) > oldPrice / 20) {
                cout << "ALERT: "
                 << name
                 << " changed by more than 5%"
                 << endl;
            }
    } 
};

class LogObserver : public StockObserver
{
private:
    char** logs;
    int size;
    int capacity;

    void copyFrom(const LogObserver& other) {
        size = other.size;
        capacity = other.capacity;
        logs = new char*[capacity];
        for (int i = 0; i < size; i++) {
            logs[i] = new char[strlen(other.logs[i]) + 1];
            strcpy(logs[i], other.logs[i]);
        }
    }

    void free() {
        for (int i = 0; i < size; i++) {
            delete[] logs[i];
        }

        delete[] logs;
    }

    void resize() {
        capacity *= 2;
        char** newLogs = new char*[capacity];
        for(int i = 0; i < size; i++) {
            newLogs[i] = logs[i];
        }
        delete[] logs;
        logs = newLogs;
    }
public:
    LogObserver(int s = 0, int c = 2) : size(0), capacity(2) {
        logs = new char*[capacity];
    }

     LogObserver(const LogObserver& other) {
        copyFrom(other);
    }

    LogObserver& operator=(const LogObserver& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }

        return *this;
    }

    void onPriceChange(const char* name, double oldPrice, double newPrice) override {
        if(size == capacity) {
            resize();
        }

        logs[size] = new char[200];
        strcpy(logs[size], name); 
        strcat(logs[size], " changed price");
        size++;
    }

    ~LogObserver() {
        free();
    }

    void printLogs() const {
        for (int i = 0; i < size; i++) {
            cout << logs[i] << endl;
        }
    }
};

class Stock
{
private:
    char* name;
    double price;

    StockObserver** observers;
    int observersCount;
    int observersCapacity;

    void resizeObservers() {
        observersCapacity *= 2;
        StockObserver** newObservers = new StockObserver*[observersCapacity];
        for (int i = 0; i < observersCount; i++) {
            newObservers[i] = observers[i];
        }
        delete[] observers;
        observers = newObservers;
    }

    void copy(const Stock& other) {
        price = other.price;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        observersCount = other.observersCount;
        observersCapacity = other.observersCapacity;
        observers = new StockObserver*[observersCapacity];
        for(int i = 0; i < observersCount; i++) {
            observers[i] = other.observers[i];
        }
    }

    void free() {
        delete[] name;
        delete[] observers;
    }
public:
    Stock(const char* n, double p, int obc = 0, int oc = 2) : price(p), observersCount(obc), observersCapacity(oc) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);

        observers = new StockObserver*[observersCapacity];
    }

    Stock(const Stock& other) {
        copy(other);
    }

    Stock& operator=(const Stock& other) {
        if(this != &other) {
            free();
            copy(other);
        }

        return *this;
    }

    ~Stock() {
        free();
    }

    const char* getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    void addObserver(StockObserver* observer) {

        if (observersCount == observersCapacity) {
            resizeObservers();
        }

        observers[observersCount] = observer;
        observersCount++;
    }

    void setPrice(double newPrice) {

        double oldPrice = price;

        price = newPrice;

        for (int i = 0; i < observersCount; i++) {

            observers[i]->onPriceChange(
                name,
                oldPrice,
                newPrice
            );
        }
    }
};

class StockMarket
{
private:
    Stock** stocks;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        Stock** newStocks = new Stock*[capacity];
        for (int i = 0; i < size; i++) {
            newStocks[i] = stocks[i];
        }
        delete[] stocks;
        stocks = newStocks;
    }
public:
    StockMarket(int s = 0, int c = 2) : size(s), capacity(c) {
        stocks = new Stock*[capacity];
    }

    ~StockMarket() {
        for (int i = 0; i < size; i++) {
            delete stocks[i];
        }
        delete[] stocks;
    }

    void addStock(Stock* stock) {
        if (size == capacity) {
            resize();
        }
        stocks[size] = stock;
        size++;
    }

    void printStocks() const {

        for (int i = 0; i < size; i++) {

            cout << stocks[i]->getName()
                 << " "
                 << stocks[i]->getPrice()
                 << endl;
        }
    }
};

int main() {

    StockMarket market;

    Stock* apple =
        new Stock("Apple", 100);

    Stock* tesla =
        new Stock("Tesla", 200);

    AlertObserver alert;
    LogObserver log;

    apple->addObserver(&alert);
    apple->addObserver(&log);

    tesla->addObserver(&alert);
    tesla->addObserver(&log);

    market.addStock(apple);
    market.addStock(tesla);

    apple->setPrice(120);
    tesla->setPrice(180);

    cout << endl;

    log.printLogs();

    return 0;
}


