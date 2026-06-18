#include <iostream>
using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;

    static bool isLeapYear(int year) {
        return  (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    static int daysInMonth(int month, int year) {
        switch (month) {
            case 1: return 31;
            case 2: return isLeapYear(year) ? 29 : 28;
            case 3: return 31;
            case 4: return 30;
            case 5: return 31;
            case 6: return 30;
            case 7: return 31;
            case 8: return 31;
            case 9: return 30;
            case 10: return 31;
            case 11: return 30;
            case 12: return 31;
            default: return 30;
        }
    }

    static bool isValidDate(int day, int month, int year) {
        if(year < 1) return false;
        if(month < 1 || month > 12) return false;
        if(day < 1 || day > daysInMonth(month, year)) return false;
        return true;
    }

public:
    Date() : day(1), month(1), year(2000) {}

    Date(int d, int m, int y) {
        if(isValidDate(d,m,y)) {
            day = d;
            month = m;
            year = y;
        } 
        else {
           cout << "Invalid date! Default value used." << endl;
           day = 1;
           month = 1;
           year = 2000;             
        }
    }

    ~Date();
};


int main() {
    return 0;
}