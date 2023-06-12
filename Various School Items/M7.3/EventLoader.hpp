//
//  EventLoader.hpp
//  M7.2
//
//  Created by Lucas Oakley on 12/5/19.
//  Copyright © 2019 LucasOakley. All rights reserved.
//

#ifndef EventLoader_hpp
#define EventLoader_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Event.hpp"

using namespace std;
//using namespace bridges;

class EventLoader {
    
public:
    EventLoader(string configLoc, string eventsLoc);
    
    string configFileLoc;
    string eventsFileLoc;
    string bridgesUser;
    string bridgesPass;
    string pyPath;
    string scPath;
    string scName;
    string readYear;
    string calImageLoc;
    Event total[1000];
    int totalEvents = 0;
    
    
    void readConfigFile();
    void readEventsFile();
    
};



#endif /* EventLoader_hpp */
