#ifndef EVENT2_H
#define EVENT2_H
#include <string>
using namespace std;

class Event2
{
    public:
    Event2();
    Event2(int m, int d);
    Event2(int m, int d, string des);

    virtual ~Event2();

    int day, month;
    string desc;

    string getEvent();
    Event2 returnWholeEvent();
    void setEvent(int m, int d, string s);
    int getDay();
    int getMonth();
    string getNameOfMonth();
    string getDesc();



    protected:
    string nameOfMonth[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    int daysInMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};

    private:
};

#endif // EVENT2_H
