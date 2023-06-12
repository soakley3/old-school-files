/**
*Event2 Class
*Used to create and store Event Objects
*/

#include "Event2.hpp"
#include <string>
#include <iostream>
using namespace std;

/**
 * Event2 Constructor
 *
 * Default Constructor, Creates an Empty Object
 */
Event2::Event2()
{
    Event2::day = NULL;
    Event2::month = NULL;
    Event2::desc = "";
}

/**
 * Event2 Constructor
 *
 * Used to create an Event Object with the Provided parameters
 *
 * @param m int value that repsresents the Month
 * @param d int value that repsresents the Day
 */
Event2::Event2(int m, int d)
{
    Event2::day = d+1;
    Event2::month = m;
    Event2::desc = "";
}

/**
 * Event2 Constructor
 *
 * Used to create an Event Object with the Provided parameters
 *
 * @param m int value that repsresents the Month
 * @param d int value that repsresents the Day
 * @param des string value that repsresents the Event Data
 */
Event2::Event2(int m, int d, string des)
{
    Event2::day = d+1;
    Event2::month = m;
    Event2::desc = des;
}

/**
 * getDay()
 *
 * Used to get and return the day value of event object
 *
 * @return int day
 */
int Event2::getDay(){return this->Event2::day;}
/**
 * getMonth()
 *
 * Used to get and return the month value of event object
 *
 * @return int month
 */
int Event2::getMonth(){return this->Event2::month;}
string Event2::getNameOfMonth(){return this->Event2::nameOfMonth[month-1];}
/**
 * getDesc()
 *
 * Used to get and return the description of the event object
 *
 * @return string desc
 */
string Event2::getDesc(){return this->Event2::desc;}


/**
 * getEvent()
 *
 * Calls and return the description of the event object using getDesc()
 *
 * @return string desc
 */
string Event2::getEvent()
{
    return getDesc();
}


/**
 * setEvent Method
 *
 * Used to overide and modify the stored data of an existing Event Object
 *
 * @param m int value that repsresents the Month
 * @param d int value that repsresents the Day
 * @param des string value that repsresents the Event Data
 */
void Event2::setEvent(int m, int d, string s)
{
    this->Event2::month = m;
    this->Event2::day = d+1;
    this->Event2::desc = s;

}

/**
 * Deconstructor
 */
Event2::~Event2()
{
    //dtor
}

