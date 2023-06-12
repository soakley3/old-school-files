/*
Created by Zowie Haugaard
9/16/16
PPM Converter
  This program is used to convert between the ascii and binary versions of the
  .ppm image file format.
 */
#ifndef ppmwrite_hpp
#define ppmwrite_hpp

#include <stdio.h>


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

using namespace std;
//using namespace bridges;

class ppmwrite {
    
public:
    void writeP3(FILE *inFile, FILE *outFile);
    
    
    
};


#endif /* ppmwrite_hpp */
