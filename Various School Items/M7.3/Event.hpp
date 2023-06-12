//
//  Event.hpp
//  M7.2
//
//  Created by Lucas Oakley on 12/5/19.
//  Copyright © 2019 LucasOakley. All rights reserved.
//

#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;


class Event {
    
public:
    int month;
    int day;
    string description;
    
    Event(int MM, int DD, string what);
    Event();
    void printEvent();
    
};


#endif /* Event_hpp */
