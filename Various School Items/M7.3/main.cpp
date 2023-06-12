//
//  main.cpp
//  M7.2
//
//  Created by Lucas Oakley on 11/16/19.
//  Copyright © 2019 LucasOakley. All rights reserved.
//


#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Bridges.h"
#include "Color.h"
#include "ColorGrid.h"
#include "Bridges.h"
#include "KdTreeElement.h"

#include "Image.hpp"
#include <SymbolCollection.h>
#include <Symbol.h>
#include <Label.h>
#include "ppmwrite.hpp"
#include "EventLoader.hpp"
#include <stdlib.h>
#include "Event2.hpp"
//#include <Python.h>



using namespace std;
using namespace bridges;

// Define the Global variables

// where all the properties of each image is stored
// This include it's colorgrid. All the pixels read from the ppm file (r, g, b, r, g, b, etc)
// And the colorgrids dimensions.
Image * images;
const int maxEvents  = 4;
int MONTHS = 12; // wont change

//Holds Data
/**
 * thisMonth
 *
 * struct used to represent a Month as an object.
 *
 * @param monthID  int value of the Month
 * @param dayID int value of the day
 * @param dayNode  KdTreeElement<int, int> used to sort the order of the days
 * @param e[int maxEvents * 31]   array of event objects used to stored the events and information of each day
 * @param monthName string that holds the actual name of the month
 *
 */
struct thisMonth
{
    int monthID;
    int dayID;
    KdTreeElement<int, int> *dayNode;
    Event2 e[maxEvents * 31];
    string monthName;
};



// Bridges login information.
//default settings are overwritten in the config.txt
string USER = "asilfies";
string PASS = "441640141151";
string YEAR = "1999";

//string pythonPath = "python";
//string scriptPath = "/Users/lucas/Projects/2019Fall/ITSC3112/M7.2/M7.2/tempImages";
//string scriptName = "textToImage.py";
//string calendarImageLocation = "/Users/lucas/Projects/2019Fall/ITSC3112/M7.2/M7.2/cal2.ppm";

string pythonPath = "";
string scriptPath = "";
string scriptName = "";
string calendarImageLocation = "";



/**
 * readPPM Method
 *
 * Reads the text values from the provide path to the calendarImage.ppm
 *
 * @param fil string value representing the pathway to the Calendar image
 * @param index int the numeric idex of image[] object
 *
 * @return c
 *
 */
void readPPM(string fil, int imageIndex) {
    ifstream reader;
    cout << fil << endl;
    reader.open(fil);
    if (!reader) {
        cout << "Could not open the file.\n";
        exit(1);
    }

    std::string line;
    string word;
    string rezx, rezy;
    string tmp, scale;
    reader >> tmp; // first val from the file.
    reader >> rezx;
    reader >> rezy;
    reader >> scale;
    // convert the x and y values of the image into the global ints

    images[imageIndex] = Image();

    images[imageIndex].dimensionX = stoi(rezx);
    images[imageIndex].dimensionY = stoi(rezy);
    images[imageIndex].pixelSize = images[imageIndex].dimensionX*images[imageIndex].dimensionY*3;
    //allocate new memory for the int[] that stores all the values to be read in the file.
    images[imageIndex].pixels = new int[images[imageIndex].pixelSize];
    int i = 0;
    // we use largest int later on to help scale the values
    // read the file "word by word" so we dont have to manipulate the string with a delimeter.
    while (reader >> word) {
        // convert the "word" to an integer and store it in the appropriate place in the int[]
        // also record the largest value
        images[imageIndex].pixels[i] = stoi(word);
        i++;
    }
    //cout << "This is " << rezx << " by " << rezy << " with the largest " << "\n";
    //return holding;
}


/**
 * createGrids Method
 *
 * Creates the Calendar image that will be displayed to the  Bridges Website
 * Reads the values provided by the ppm file, then sets those values to the color grid in the images[index].cg object.
 *
 * @param bridges information used to project visuals onto bridges website
 * @param index int the numeric idex of image[] object
 *
 */
//reads teh values provided by the ppm file, then sets those values to the color
// grid in the images[index].cg object.
void createGrid(Bridges* bridges, int index) {
    images[index].cg = new ColorGrid(
            images[index].dimensionY,
            images[index].dimensionX,
            Color("white")
    );
    int ticker = 0;
    for (int j = 0; j < images[index].dimensionY;  j++) {
        for (int k = 0; k < images[index].dimensionX;  k++) {
            int tr, tg, tb;
            // get and store each r g b value from the large 1d array
            tr = images[index].pixels[ticker];
            ticker++;
            tg = images[index].pixels[ticker];
            ticker++;
            tb = images[index].pixels[ticker];
            images[index].cg->set(j, k, Color(tr, tg, tb));
            //images[index].cg->
            // store the colour value in a map for access during the greedy method.
            ticker++;
            //cout << "rgb - " << tr << ", " << tg << ", " << tb << "\n";
        }
    }
}


/**
 * createGrids Method
 *
 * Creates the Calendar image that will be displayed to the  Bridges Website
 *
 * @param bridges information used to project visuals onto bridges website
 *
 *
 */
void createGrids(Bridges* bridges) {
    for (int i = 0; MONTHS > i; i++) {
        cout << "Generating calendar background image " << i << "\n";
        createGrid(bridges, i);
    }
}


/**
 * Display Method
 *
 * Generates the Calendar image onto the Bridges Website
 *
 * @param bridges information used to project visuals onto bridges website
 * @param index int the numeric idex of image[] object
 *
 */
// displays whatever images[index].cg colour grid selected by the index provided.
void display(Bridges* bridges, int index) {
    //bridges->setTitle("M6.3");
    bridges->setDataStructure(images[index].cg);
    //bridges->
    cout << "found vis " << index << "\n";
    bridges->visualize();
}


/**
 * generateText
 *
 * used to create the text visual of events
 *
 * @param toGenerate string to be generated as a textbox
 *
 */
Image generateText(string toGenerate) {
    string toRun = pythonPath + " " +scriptPath + "/" + scriptName + " " + scriptPath + " " +toGenerate;
    system(toRun.c_str());
    //cout << toRun << "\n";
    sleep(0.25);
    //cout << "last message\n";

    string p6 = scriptPath + "/" +"tester.ppm";
    string p3 = scriptPath + "/" +"tester2.ppm";
    char p6c[p6.size()+1];
    char p3c[p6.size()+2];

    strcpy(p6c, p6.c_str());
    strcpy(p3c, p3.c_str());

    FILE *reader6 = fopen(p6c, "rb");
    FILE *reader3 = fopen(p3c, "wb");

    ppmwrite writer = ppmwrite();
    writer.writeP3(reader6, reader3);

    ifstream reader;
    reader.open(p3);
    if (!reader) {
        cout << "Could not open the file.\n";
        exit(1);
    }

    std::string line;
    string word;
    string rezx, rezy;
    string tmp, scale;
    reader >> tmp; // first val from the file.
    reader >> rezx;
    reader >> rezy;
    reader >> scale;
    // convert the x and y values of the image into the global ints

    Image text = Image();

    text.dimensionX = stoi(rezx);
    text.dimensionY = stoi(rezy);
    text.pixelSize = text.dimensionX*text.dimensionY*3;
    //allocate new memory for the int[] that stores all the values to be read in the file.
    text.pixels = new int[text.pixelSize];
    int i = 0;
    // we use largest int later on to help scale the values
    // read the file "word by word" so we dont have to manipulate the string with a delimeter.
    while (reader >> word) {
        // convert the "word" to an integer and store it in the appropriate place in the int[]
        // also record the largest value
        text.pixels[i] = stoi(word);
        i++;
    }

    return text;
}


/**
 * drawTextOnDay
 *
 * used to retrieve and create the text visuals used by the calandar for events
 *
 * @param bridges int numeric value of the month
 * @param what string that represents the event
 * @param motn int numeric value of the month
 * @param day int numeric value of the day
 *
 */
void drawTextOnDay(Bridges* bridges, string what, int month, int day) {
    //if (images[month].calendarEntries[day] < 0)
      //  images[month].calendarEntries[day] = 0;
    //cout << "Previous image " << "MONTH: " << month << " DAY: " << day << " "<< images[month].calendarEntries[day] << "\n";
    Image text = generateText(what);
    int ticker = 0;
    for (int j = 0; j < text.dimensionY;  j++) {
        for (int k = 0; k < text.dimensionX;  k++) {
            int tr, tg, tb;
            // get and store each r g b value from the large 1d array
            tr = text.pixels[ticker];
            ticker++;
            tg = text.pixels[ticker];
            ticker++;
            tb = text.pixels[ticker];
            // determine day x y adjustment.
            int xAdj = 0;
            int yAdj = 50;
            int entryAdj = entryAdj = 25 * images[month].calendarEntries[day];
            //if ((images[month].calendarEntries[day] > -1) && (images[month].calendarEntries[day] < 6))
                //entryAdj = 25 * images[month].calendarEntries[day];

            if (day >= 0 && day <= 6) {

            }
            if (day >= 7 && day <= 13) {
                yAdj += 215;
            }
            if (day >= 14 && day <= 20) {
                yAdj += 2*215;
            }
            if (day >= 21 && day <= 27) {
                yAdj += 3*215;
            }
            if (day >= 28 && day <= 35) {
                yAdj += 4*215;
            }
            if (day == 1 || day == 8 || day == 15 || day == 22 || day == 29) {
                xAdj += 275;
            }
            //3 10 17 24 31
            if (day == 2 || day == 9 || day == 16 || day == 23 || day == 30) {
                xAdj += 2*275;
            }
            if (day == 3 || day == 10 || day == 17 || day == 24 || day == 31) {
                xAdj += 3*275;
            }
            if (day == 4 || day == 11 || day == 18 || day == 25 || day == 32) {
                xAdj += 4*275;
            }
            if (day == 5 || day == 12 || day == 19 || day == 26 || day == 33) {
                xAdj += 5*275;
            }
            if (day == 6 || day == 13 || day == 20 || day == 27 || day == 34) {
                xAdj += 6*275;
            }

            images[month].cg->set(j + yAdj + entryAdj, k + xAdj, Color(tr, tg, tb));
            //images[index].cg->
            // store the colour value in a map for access during the greedy method.
            ticker++;
            //cout << "rgb - " << tr << ", " << tg << ", " << tb << "\n";
        }
    }
    // this increases the entry count so that the text-image generator does not
    // overwrite any previous entries.
    images[month].calendarEntries[day]++;
}


/**
 * makeMonth
 *
 * used to create the "month" object used to store the calendar data
 *
 * @param n KdTreeElement<int, int> based node object that represents a single day of the month
 * @param key int numeric value used to sort nodes
 * @param count unused int value. defaults to 0
 *
 *return n Returns the updated KdTree node
 *
 */
//Builds Tree
KdTreeElement<int, int>  *makeMonth (KdTreeElement<int, int> *n, int key, int count)
{
   KdTreeElement<int, int> *oldLeft = NULL;
   KdTreeElement<int, int> *rAdd = n;
   KdTreeElement<int, int> *rside = NULL;
   KdTreeElement<int, int> *lside = NULL;
   if(n->getKey() == NULL){
       n = new KdTreeElement<int, int>(key, count);
       n->setLeft(lside);
       n->setRight(rside);
   }
   while(rAdd->getKey() != NULL){
       // cout << "Adding " << key << " after "<< rAdd->getKey()<<endl;
        oldLeft = rAdd;
        //if key is Less then key checked, set as left child

       if(key < rAdd->getKey()){
        cout << "ERROR" << endl;
        break;
       }

       //if key is greater then key checked, set as left child
        else if(key > rAdd->getKey()){

           if(rAdd->getLeft() == NULL){
            rAdd->setLeft( new KdTreeElement<int, int>(key, count) );
            break;
        }
        //Set to Move
        rAdd = rAdd->getLeft();
       }
   }
   return n;
}


thisMonth months[12];


/**
 * addEvent
 *
 * adds an event to the object based on the parameters passed into it
 *
 * @param m int numeric value of the month
 * @param d int numeric value of the day
 * @param s string that represents the event
 *
 */
//Add Data to event node
void addEvent(int m, int d, int i, string s){
    if(m < 0){m=0;} else if(m > 11){m=11;}
    if(d < 0){d=0;} else
    if(d >= months[m].dayID){d=months[m].dayID;}
    if(i < 0){i=0;} else if(i > 3){i=3;}

    months[m].e[(maxEvents * d) + i].setEvent(m,d,s);
}


/**
 * pullEvent
 *
 * Generates and Retrieves a string that diplays
 the output of the data stored in the chosen event object
 *
 * @param m int numeric value of the month
 * @param d int numeric value of the day
 * @param i int numeric call to event[] in the object
 *
 * @return string toString() of the Event
 */
 //toString of event node
string pullEvent(int m, int d, int i){
    if(m < 0){m=0;} else if(m > 11){m=11;}
    if(d < 0){d=0;} else
    if(d >= months[m].dayID){d=months[m].dayID;}
    if(i < 0){i=0;} else if(i > 3){i=3;}

    return months[m].e[(maxEvents * d) + i].getDesc();
}

/**
 * getEventDay
 *
 * Get the day value stored in the event Object
 *
 * @param m int numeric value of the month
 * @param d int numeric value of the day
 * @param i int numeric call to event[] in the object
 *
 * @return int The value of the day stored in the event object
 */
int getEventDay(int m, int d, int i){
    if(m < 0){m=0;} else if(m > 11){m=11;}
    if(d < 0){d=0;} else
    if(d >= months[m].dayID){d=months[m].dayID;}
    if(i < 0){i=0;} else if(i > 3){i=3;}

    return months[m].e[(maxEvents * d) + i].getDay();
}

/**
 * getEventMonth
 *
 * Get the month value stored in the event Object
 *
 * @param m int numeric value of the month
 * @param d int numeric value of the day
 * @param i int numeric call to event[] in the object
 *
 * @return int The value of the month stored in the event object
 */
int getEventMonth(int m, int d, int i){
    if(m < 0){m=0;} else if(m > 11){m=11;}
    if(d < 0){d=0;} else
    if(d >= months[m].dayID){d=months[m].dayID;}
    if(i < 0){i=0;} else if(i > 3){i=3;}

    return months[m].e[(maxEvents * d) + i].getMonth();
}

/**
 * getEventDesc
 *
 * Get the string stored in the event Object that holds the Description of the Event
 *
 * @param m int numeric value of the month
 * @param d int numeric value of the day
 * @param i int numeric call to event[] in the object
 *
 * @return string Description of the Event
 */
string getEventDesc(int m, int d, int i){
    if(m < 0){m=0;} else if(m > 11){m=11;}
    if(d < 0){d=0;} else
    if(d >= months[m].dayID){d=months[m].dayID;}
    if(i < 0){i=0;} else if(i > 3){i=3;}

    return months[m].e[(maxEvents * d) + i].getDesc();
}

/**
 * getEventNameOfMonth
 *
 * Get the string stored in the event Object that holds the name of the month
 *
 * @param m int numeric value of the month
 * @param d int numeric value of the day
 * @param i int numeric call to event[] in the object
 *
 * @return string The name of the month stored event object
 *
 */
string getEventNameOfMonth(int m, int d, int i){
    if(m < 0){m=0;} else if(m > 11){m=11;}
    if(d < 0){d=0;} else
    if(d >= months[m].dayID){d=months[m].dayID;}
    if(i < 0){i=0;} else if(i > 3){i=3;}

    return months[m].e[(maxEvents * d) + i].getNameOfMonth();
}







int main2(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";


    images = new Image[MONTHS];

    /* This is probably the least efficient way this could be done.
     This reads the same PPM file 12 times, and then creates 12 separate ColorGrids.

     The ColoGrid is 1920x1080, and creating 12 of those uses a lot of memory. It also seems that when displaying this on Bridges, the website is sluggish due to the amount of data.

     Reused from another assignment. It may be smarter to load the cal2 image once, then
     access it via a pointer? But then what about drawing on it? Because if you draw on it directly it will affect the other calendars.
     */

    for (int i = 0; MONTHS > i; i++) {
        readPPM(calendarImageLocation, i);
        //images[i].printDemims();
    }


    readPPM(calendarImageLocation, 0);

    Bridges *bridges = new Bridges(7, USER,
    PASS);


    createGrids(bridges);
    // name the months
    string mons[] = {"January", "February", "March", "April", "May", "June", "July",
                     "August", "September", "October", "November", "December"};
    for (int i = 0; MONTHS > i; i++) {
        drawTextOnDay(bridges, YEAR, i, 34);
        drawTextOnDay(bridges, mons[i], i, 34);
    }





    // test cases
    drawTextOnDay(bridges, "hello", 0, 30);
    drawTextOnDay(bridges, "1", 1, 1);
    drawTextOnDay(bridges, "gracias", 2, 15);
    drawTextOnDay(bridges, "test", 0, 18);
    drawTextOnDay(bridges, "fifteen", 0, 28);
    drawTextOnDay(bridges, "yodel", 0, 30);
    drawTextOnDay(bridges, "yodel", 11, 13);
    drawTextOnDay(bridges, "Birthday", 11, 25);
    drawTextOnDay(bridges, "Birthday1", 11, 25);
    drawTextOnDay(bridges, "Birthday2", 11, 25);

    for (int i = 0; MONTHS > i; i++) {
        display(bridges, i);
    }
    /*
    cout << "\n\n\n\n\n\n------\n";
    cout << "Presented in Bridges is your calendar.\n";
    cout << "Lets get busy! Add more in the format MM-DD-YEAR.\n...";
    string date1 = "";
    cin >> date1;
    cout << "Enter event.\n...";
    string event = "";
    cin >> event;
    cout << "Displaying event '" << event << "' on day " << date1 << "\n";*/
    return 0;
}

int main3(int argc, const char * argv[]) {
    //EventLoader loader = EventLoader("/Users/lucas/Projects/2019Fall/ITSC3112/M7.2/M7.2/config.txt", "/Users/lucas/Projects/2019Fall/ITSC3112/M7.2/M7.2/events.txt");
    EventLoader loader = EventLoader("/Users/lucas/Projects/2019Fall/ITSC3112/M7.3/M7.3/config.txt", "/Users/lucas/Projects/2019Fall/ITSC3112/M7.3/M7.3/events.txt");

    cout << loader.scPath << "\n";
    cout << loader.pyPath << "\n";
    return 0;
}

int main(int argc, char **argv) {

    std::cout << "Hello, World!\n";
    //EventLoader loader = EventLoader("/Users/lucas/Projects/2019Fall/ITSC3112/M7.2/M7.2/config.txt", "/Users/lucas/Projects/2019Fall/ITSC3112/M7.2/M7.2/events.txt");
    EventLoader loader = EventLoader("/home/user/Final/M7.2/config.txt", "/home/user/Final/M7.2/events.txt");

    if (loader.bridgesUser.compare("") != 0) USER = loader.bridgesUser;
    if (loader.bridgesPass.compare("") != 0) PASS = loader.bridgesPass;
    if (loader.pyPath.compare("") != 0) pythonPath = loader.pyPath;
    if (loader.scPath.compare("") != 0) scriptPath = loader.scPath;
    if (loader.scName.compare("") != 0) scriptName = loader.scName;
    if (loader.readYear.compare("") != 0) YEAR = loader.readYear;
    if (loader.calImageLoc.compare("") != 0) calendarImageLocation = loader.calImageLoc;

    // name the months
    //string mons[] = {"January", "February", "March", "April", "May", "June", "July",
      //                  "August", "September", "October", "November", "December"};
    string nameOfMonth[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};

    int daysInMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    // create nodes

    for(int i = 0; i < 12; i++) {
        months[i].dayNode = new KdTreeElement<int, int>(NULL, NULL);
        months[i].monthID = i;
        months[i].monthName = nameOfMonth[i];
        months[i].dayID = daysInMonth[i];

        for(int j = 0; j < months[i].dayID; j++) {
            //cout<< "DEBUG "<<j+1 <<" of "<< months[i].monthName <<endl;
            *months[i].dayNode = *makeMonth(months[i].dayNode, j, 0);
            months[i].e[0+j*maxEvents]={ months[i].monthID, j};
            months[i].e[1+j*maxEvents]={ months[i].monthID, j};
            months[i].e[2+j*maxEvents]={ months[i].monthID, j};
            months[i].e[3+j*maxEvents]={ months[i].monthID, j};
        }
    }


    for (int i = 0; loader.totalEvents > i; i++) {
        int h = 0;
        if (getEventDesc(loader.total[i].month, loader.total[i].day, h).compare("") != 0)
            h++;
        if (getEventDesc(loader.total[i].month, loader.total[i].day, h).compare("") != 0)
            h++;
        if (getEventDesc(loader.total[i].month, loader.total[i].day, h).compare("") != 0)
            h++;
        if (getEventDesc(loader.total[i].month, loader.total[i].day, h).compare("") != 0)
            h++;
        addEvent(loader.total[i].month, loader.total[i].day, h, loader.total[i].description);
    }


    images = new Image[MONTHS];
    for (int i = 0; MONTHS > i; i++) {
        readPPM(calendarImageLocation, i);
        images[i].printDemims();
    }

    readPPM(calendarImageLocation, 0);

    Bridges *bridges = new Bridges(7, USER, PASS);
cout<<"Throw Error\n";
    createGrids(bridges);
cout<<"Error Thrown\n";
    for (int i = 0; MONTHS > i; i++) {
        drawTextOnDay(bridges, YEAR, i, 34);
        drawTextOnDay(bridges, nameOfMonth[i], i, 34);
    }

    string weekDays[] = {"Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday"};
    int wdCount = 0;

    for (int i = 0; MONTHS > i; i++) {
        for (int j = 0; daysInMonth[i] > j; j++) {
            //cout << "WD - " << i << ", " << j << " = " << weekDays[wdCount] << endl;
            drawTextOnDay(bridges, weekDays[wdCount], i, j);
            wdCount++;
            if (wdCount == 7) wdCount = 0;
        }
    }

    cout << "checking the kdtree\n";
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < months[i].dayID; j++) {
            for (int k = 0; 4 > k; k++) {
                if (getEventDesc(i, j, k).compare("") != 0) {
                    cout << "found event " << getEventDesc(i, j, k) << "\n";
                    drawTextOnDay(bridges, getEventDesc(i, j, k), i, j);
                }
            }
        }
    }

    for (int i = 0; MONTHS > i; i++) {
        display(bridges, i);
    }

    return 0;
}
