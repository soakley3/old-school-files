//
//  Image.hpp
//  M6
//
//  Created by Lucas Oakley on 10/31/19.
//  Copyright © 2019 LucasOakley. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

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
//#include "ColorGrid.h"
#include "Bridges.h"
#include "KdTreeElement.h"


using namespace std;
using namespace bridges;


class Image {
    
public:
    Image();
    Image(int* p);
    
    int* pixels;
    int dimensionX, dimensionY, pixelSize,
        avgR, avgG, avgB;
    ColorGrid *cg;//  = new ColorGrid(1000, 1000, Color("white"));
    string name;

    void printDemims();
    //void createColorGrid();
    
    
};

#endif /* Image_hpp */
