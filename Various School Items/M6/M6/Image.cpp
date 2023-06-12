//
//  Image.cpp
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

Image::Image() {
    dimensionX = 0;
    dimensionY = 0;
    pixelSize = 0;
    ColorGrid *cg = new ColorGrid();
    
}

/*void Image::createColorGrid() {
    cg = new ColorGrid(dimensionX, dimensionY, Color("white"));
}*/


void Image::printDemims() {
    cout << "Demims: size - " << pixelSize << ", x - " << dimensionX << ", y - " << dimensionY << "\n";
}
