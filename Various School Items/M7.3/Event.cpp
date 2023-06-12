/**
*Event Class
*Used to create and store Event Objects
*/
//
//  Event.cpp
//  M7.2
//
//  Created by Lucas Oakley on 12/5/19.
//  Copyright © 2019 LucasOakley. All rights reserved.
//

#include "Event.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

/**
 * Event Constructor
 *
 * Used to create an Event Object with the Provided parameters
 *
 * @param MM int value that repsresents the Month
 * @param DD int value that repsresents the Day
 * @param what string value that repsresents the Event Data
 */
Event::Event(int MM, int DD, string what) {
    month = MM;
    day = DD;
    description = what;
}

/**
 * Event Constructor
 *
 * Default Constructor, Creates an Empty Object
 */
Event::Event() {

}

/**
 * PrintEvent()
 * Prints a line of text into the console that shows the basic information of the Event Object
 */
void Event::printEvent() {
    cout << "On month " << month << ", day " << day << " - " << description << "\n";
}
