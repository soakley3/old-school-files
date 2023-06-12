/**
* EventLoader Class
*
* Class is used to load and read the Config.txt and Events,txt files.
to retrieve login and pathing data used by other methods.
*/
//
//  EventLoader.cpp
//  M7.2
//
//  Created by Lucas Oakley on 12/5/19.
//  Copyright © 2019 LucasOakley. All rights reserved.
//

#include "EventLoader.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Event.hpp"

using namespace std;

/**
 * setEvent Method
 *
 * Void method used to store the locations of text files
 * used to generate and load the calendar events.
 * Reads the files and call the load methods
 * @param configLoc string that represent stored file location of Config.txt
 * @param eventsLoc string that represent stored file location of events.txt
 */
EventLoader::EventLoader(string configLoc, string eventsLoc) {
    total[1000];
    for (int i = 0; 1000 > i; i++) {
        total[i] = Event();
    }
    configFileLoc = configLoc;
    eventsFileLoc = eventsLoc;
    readConfigFile();
    readEventsFile();

    /*for (int i = 0; 1000 > i; i++) {
        total[i];// = NULL;
    }*/
}

/**
 * readConfigFile Method
 *
 * method is is used to read Config.txt.
 * method scans the config and retrieves the data used for Bridges login data, path of the Calendar Image,
 and the path of the python scripted used to create the event visuals
 * Sets the data of the chosen Event object using Event::Event(int MM, int DD, string what)
 *
 */
void EventLoader::readConfigFile() {
    ifstream reader;
    reader.open(configFileLoc);
    if (!reader) {
        cout << "Could not open the file.\n";
        exit(1);
    }
    std::string line;
    string word;
    string tempHolder = "";
    while (reader >> word) {
        if (word.compare("USER") == 0){
            reader >> word;
            bridgesUser = word;
        }
        if (word.compare("PASS") == 0){
            reader >> word;
            bridgesPass = word;
        }
        if (word.compare("PythonPath") == 0){
            reader >> word;
            pyPath = word;
        }
        if (word.compare("ScriptPath") == 0){
            reader >> word;
            scPath = word;
        }
        if (word.compare("ScriptName") == 0){
            reader >> word;
            scName = word;
        }
        if (word.compare("calendarImageLocation") == 0){
            reader >> word;
            calImageLoc = word;
        }
    }
    cout << "Configuration loaded\n";
}

/**
 * readEventsFile Method
 *
 * method is is used to read events.txt from the pathway assigned in Config.txt
 * method scans and tokenizes the contents of the file.
 * Detects the desire Day and Month provide and calculates the targeted Event Object.
 * Sets the data of the chosen Event object using Event::Event(int MM, int DD, string what)
 */
void EventLoader::readEventsFile() {
    ifstream reader;
    reader.open(eventsFileLoc);
    if (!reader) {
        cout << "Could not open the file.\n";
        exit(1);
    }
    cout << "step 1\n";
    std::string line;
    string word;
    string tempHolder = "";
    reader >> word;
    readYear = word;
    cout << readYear << "\n";
    // step 0 - reading year
    // step 1 - reading month
    // step 2 - reading day (int)
    // step 3 - reading description
    int step = 0;
    int currentMonth = -1;
    int currentDay = -1;
    string currentDesc = "";
    //cout << "step 2\n";
    bool skipper = false;
    while (reader >> word) {
        if (word.compare("{") == 0) {
            step++;
            reader >> word;
            if (word.compare("MONTH") == 0) {
                reader >> word;
                currentMonth = stoi(word);
                skipper = false;
                //cout << "NEW MONTH - " << currentMonth << endl;
                step++;
            }
        }
        if (word.compare("}") == 0) {
            //cout << "ending month\n";
            step = 0;
        }
        if (step == 2) {
            //cout << "skipper - " << skipper << endl;
            if (!skipper) {
                reader >> word;
            } else {
                skipper = false;
            }
            //cout << " --" << word << "\n";
            currentDay = stoi(word);
            //step++;
            while (reader >> word) {
                //reader >> word;
                currentDesc += word + " ";
                if (word.find(".") != std::string::npos) {
                    skipper = true;
                    break; // leave the loop
                }
                // end of description.
            }
            cout << "adding event\n";
            total[totalEvents] = Event(currentMonth, currentDay, currentDesc);
            totalEvents++;
            currentDesc = "";

            //step = 1;
        }

    }
    //cout << "step 4\n";
    for (int i = 0; totalEvents > i; i++)
        total[i].printEvent();
}

