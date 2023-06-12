//
//  Image.cpp
/**
*Image Class
*
*Used to create the Image Objects used to Store and generate the Calendar visual on Bridges
*
*/
//  M6
//
//  Created by Lucas Oakley on 10/31/19.
//  Copyright © 2019 LucasOakley. All rights reserved.
//


#include <stdio.h>
#include "string"
#include <iostream>
//#include "ColorGrid.h"
#include "Bridges.h"
#include "Color.h"

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

using namespace std;
using namespace bridges;

/**
*
* Image Constructor
*
* Constructs the image object used to visualize the calendar onto bridges
*
*/

Image::Image() {
    dimensionX = 0;
    dimensionY = 0;
    pixelSize = 0;
    ColorGrid *cg = new ColorGrid();
    for (int i = 0; 35 > i; i++) {
        calendarEntries[i] = 0;
    }
}

/*void Image::createColorGrid() {
    cg = new ColorGrid(dimensionX, dimensionY, Color("white"));
}*/

/**
*
* printDemims Method
*
* Prints the pixel ammount of the image, along with the width and height.
*
*/
void Image::printDemims() {
    cout << "Demims: size - " << pixelSize << ", x - " << dimensionX << ", y - " << dimensionY << "\n";
}
