#include <iostream>
#include <cstring>
using namespace std;

class TimeSlot
{
private:
    int startHour;
    int startMinutes;
    int endHour;
    int endMinutes;
public:
    TimeSlot(int sh = 0, int sm = 0 , int eh = 0, int em = 0) : startHour(sh), startMinutes(sm), endHour(eh), endMinutes(em) {}

    int getStartInMinutes() const {
        return startHour * 60 +  startMinutes;
    }

    int getEndInMinutes() const {
        return endHour * 60 + endMinutes;
    }

    bool overlapsWith(const TimeSlot& other) const {
        return getStartInMinutes() < other.getEndInMinutes() && other.getStartInMinutes() < getEndInMinutes();
    }

    void print() const {
        cout << startHour << ":";

        if (startMinutes < 10) {
            cout << "0";
        }

        cout << startMinutes << " - " << endHour << ":";

        if (endMinutes < 10) {
            cout << "0";
        }

        cout << endMinutes;
    }
};

class Lecture {
    char subject[50];
    char professor[50];
    TimeSlot timeSlot;

public:
    Lecture(const char* s = "", const char* p = "",
            int sh = 0, int sm = 0, int eh = 0, int em = 0)
        : timeSlot(sh, sm, eh, em)
    {
        strncpy(subject, s, 49);
        subject[49] = '\0';

        strncpy(professor, p, 49);
        professor[49] = '\0';
    }

    const TimeSlot& getTimeSlot() const {
        return timeSlot;
    }

    void print() const {
        cout << subject << " - " << professor << " | ";
        timeSlot.print();
        cout << endl;
    }
};

class DaySchedule
{
private:
    Lecture lectures[20];
    int lectureCount;
public:
    DaySchedule() : lectureCount(0) {}
    
    bool hasConflict(const Lecture& newLecture) const {
        for(int i = 0 ; i < lectureCount; i++) {
            if(lectures[i].getTimeSlot().overlapsWith(newLecture.getTimeSlot())) {
                return true;
            }
        }

        return false;
    }

    void addLecture(const Lecture& lecture) {
        if (lectureCount >= 20) {
            cout << "Няма място за повече лекции." << endl;
            return;
        }

        if (hasConflict(lecture)) {
            cout << "Конфликт в разписанието! Лекцията не е добавена." << endl;
            return;
        }

        lectures[lectureCount++] = lecture;
    }

    void print() const {
        cout << "Разписание:" << endl;

        for (int i = 0; i < lectureCount; i++) {
            lectures[i].print();
        }
    }
};

int main() {
    DaySchedule schedule;

    Lecture l1("OOP", "Ivanov", 9, 0, 10, 30);
    Lecture l2("Math", "Petrov", 10, 30, 12, 0);
    Lecture l3("Algorithms", "Georgiev", 10, 0, 11, 0);

    schedule.addLecture(l1);
    schedule.addLecture(l2);
    schedule.addLecture(l3);

    schedule.print();

    return 0;
}
