#include <iostream>
using namespace std;

class Time {
    private:
    int hours;
    int minutes;
    int seconds;
    public:
    Time(const int h, const int m, const int s) {
        hours = (h >= 0 && h <= 23) ? h : 0;
        minutes = (m >= 0 && m <= 59) ? m : 0;
        seconds = (s >= 0 && s <= 59) ? s : 0;
    }

    int toSeconds() const {
        return hours * 3600 + minutes * 60 + seconds; 
    }

    bool isAfter(const Time& other) const {
        return toSeconds() > other.toSeconds();
    }

    void addSeconds(int s) {
        int total = toSeconds() + s;

        total = total % (24 * 3600);

        if(total < 0) {
            total += 24 * 3600;
        }

        hours = total / 3600;
        total %= 3600;

        minutes = total / 60;
        total %= 60;

        seconds = total;
    }

    void print() const {
        if(hours < 10) cout << "0";
        cout << hours << ":";

        if(minutes < 10) cout << "0";
        cout << minutes << ":";

        if(seconds < 10) cout << "0";
        cout << seconds << endl;
    }
};

int main() {
    Time t1(23, 59, 50);

    cout << "Initial time: ";
    t1.print();

    t1.addSeconds(20); 

    cout << "After adding 20 sec: ";
    t1.print();

    Time t2(0, 0, 5);

    if(t1.isAfter(t2)) {
        cout << "t1 is after t2\n";
    } else {
        cout << "t1 is not after t2\n";
    }

    return 0;
}