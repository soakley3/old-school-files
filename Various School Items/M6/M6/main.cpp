//
//  main.cpp
//  M6
//
//  Created by Lucas Oakley on 10/27/19.
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


using namespace std;
using namespace bridges;


KdTreeElement<int, int>  *insertKdTree (int *values, int count);
void ColorRegion(int index, int x1, int y1, int x2, int y2);
void drawRegionEdge(int index, int x1, int y1, int x2, int y2);
// res_x and res_y store the size of the image.
// This is found in the first two values of the .dat
int FILE_COUNT = 0;
int MAX_DIFF = 5;
int MAX_LEVELS = 10;

//pixelsSize is later calculated to be res_x*res_y to store each value read from the file.
// later on, the program stores a new int[pixelsSize] in this to store all the values read
// from the file.
// stores file location


// where all the properties of each image is stored
Image * images;



bool isHomegeneous(int index, int x1, int y1, int x2, int y2);

void readFile(string fil, int imageIndex) {
    ifstream reader;
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
    cout << "This is " << rezx << " by " << rezy << " with the largest " << "\n";
    //return holding;
}

KdTreeElement<int, string> *buildImageTree (
    int *region,    // region - xmin, ymin, xmax, ymax
    int level,      // level of the tree, starts at 0 for root
    ColorGrid *cg,   // the region - originally the entire image
    bool dim_flag
);  // partitioning dimension, will flip with each
//  level



KdTreeElement<int, int> *insertKdTree (int *values, int count) {
    if (count < 1) {
        cout << "Invalid count to return the tree\n";
        return NULL;
    }
    int p = (count/2);
    int ticker = 0;
    KdTreeElement<int, int> *t[p];
    cout << "p " << p << "\n";
    t[0] = new KdTreeElement<int, int>(values[0], values[1]);
    ticker++;
    for (int j = 2; count > j; j++) {
        cout << "j1 = " << j << ", ticker = " << ticker << "\n";
        t[ticker] = new KdTreeElement<int, int>(values[j], values[(j+1)]);
        if (values[(j+1)] == 0)
            t[ticker]->setLabel("X");
        else
            t[ticker]->setLabel("Y");
        ticker++;
        j++;
    }
    cout << "ticker === " << ticker << "\n";
    int counter = 1;
    for (int j = 0; ticker > counter; j++) {
        cout << "j2 = " << j << " - "<< counter << "\n";
        t[j]->setLeft(t[counter]);
        counter++;
        t[j]->setRight(t[counter]);
        counter++;
    }
    

    return t[0];
}

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
            // store the colour value in a map for access during the greedy method.
            //map[j][k] = pixels[ticker];
            ticker++;
            //cout << "rgb - " << tr << ", " << tg << ", " << tb << "\n";
        }
    }
    
}

// builds and adds each region to a left or right branch of the binary tree.
KdTreeElement<int, int> *buildImageTree (
    int imageIndex,
    int *region,    // region - xmin, ymin, xmax, ymax
    int level,   // the region - originally the entire image
    bool dim_flag )  // partitioning dimension, will flip with each
//  level
{
    // create a kd tree element
    KdTreeElement<int, int> *root = new KdTreeElement<int, int>(imageIndex, level);//;(imageIndex, region, level, images[imageIndex].cg, dim_flag);
    
    
    // check the region's homogeneity
    bool homogeneous = isHomegeneous(imageIndex, region[0], region[1], region[2], region[3]);
    
    if ((level < MAX_LEVELS) && !homogeneous) {   // partition
        if (!dim_flag){     // partition on X
            // choose a partioning value between xmin and xmax
            //partition = partition(.... )
            //             x2    -     x1
            //  choose the middle x value for partitioning
            //          newX = x1 + (x2-x1)/2
            int xPart = region[0] + ((region[2] - region[0])/2.0);
            // form the two partitioned regions, left and right
            int lregion[] = {region[0], region[1], xPart, region[3]};
            int rregion[] = {xPart, region[1], region[2], region[3]};
            // recurse
            root->setLeft(buildImageTree (imageIndex, lregion, level+1, !dim_flag));
            root->setRight(buildImageTree (imageIndex, rregion, level+1, !dim_flag));

        } else {              // partition on Y
            int yPart = region[1] + ((region[3]-region[1])/2.0);    // ditto... for partitioning on the Y dimension, similar to X but regions
                // will be bottom and top regions
            int lregion[] = {region[0], region[1], region[2], yPart};
            int rregion[] = {region[0], yPart, region[2], region[3]};
            root->setLeft(buildImageTree (imageIndex, lregion, level+1, !dim_flag));
            root->setRight(buildImageTree (imageIndex, rregion, level+1, !dim_flag));
              
        }
 
        //ColorRegion ( ......, "white"...)
                                         
        return root;
    }
                                        
    // region is homogeenous, color it using the average
    // color of the region (compute avg in r, g, b separately
    ColorRegion (imageIndex, region[0], region[1], region[2], region[3]);
    drawRegionEdge (imageIndex, region[0], region[1], region[2], region[3]);
    return root;
}

// creates a white box barrier between every region at the extremity of the region.
void drawRegionEdge(int index, int x1, int y1, int x2, int y2) {
    ColorGrid *grid = images[index].cg;
    x2--;
    for (int j = y1; y2 > j; j++) {
        grid->set(j, x1, Color(255, 255, 255));
        grid->set(j, x2, Color(255, 255, 255));
    }
    x2++;
    y2--;
    for (int i = x1; x2 > i; i++) {
        grid->set(y1, i, Color(255, 255, 255));
        grid->set(y2, i, Color(255, 255, 255));
    }
}


// set the whole region provided to the average color discovered.
void ColorRegion(int index, int x1, int y1, int x2, int y2) {
    ColorGrid *grid = images[index].cg;
    int avgR = 0;
    int avgG = 0;
    int avgB = 0;
    int ticker = 0;
    for (int i = y1; y2 > i; i++) {
        for (int j = x1; x2 > j; j++) {
            avgR += grid->get(i, j).getRed();
            avgG += grid->get(i, j).getGreen();
            avgB += grid->get(i, j).getBlue();
            ticker++;
        }
    }
    avgR = avgR/(ticker + 0.0);
    avgG = avgG/(ticker + 0.0);
    avgB = avgB/(ticker + 0.0);
    for (int i = y1; y2 > i; i++) {
        for (int j = x1; x2 > j; j++) {
            grid->set(i, j, Color(avgR, avgG, avgB));
        }
    }
    
}
                           
                           
// pass in the index of the Image we're processing
// this will return true or false depending on if the average values are within the spec of the
// max differential provided.
bool isHomegeneous(int index, int x1, int y1, int x2, int y2) {
    ColorGrid *grid = images[index].cg;
                                             
    // clear the previous test results for a new fresh set

    // set the min to max so that it is almost guaranteed to be lowered.
    int minR = 255, maxR = 0;
    int minG = 255, maxG = 0;
    int minB = 255, maxB = 0;
    int ticker = 0;
                                             
    for (int i = y1; y2 > i; i++) {
        for (int j = x1; x2 > j; j++) {
            int curR = grid->get(i, j).getRed();
            if (curR > maxR)
                maxR = curR;
            if (curR < minR)
                minR = curR;
            int curG = grid->get(i, j).getGreen();
            if (curG > maxG)
                maxG = curG;
            if (curG < minG)
                minG = curG;
            int curB = grid->get(i, j).getBlue();
            if (curB > maxB)
                maxB = curB;
            if (curB < minB)
                minB = curB;
            images[index].avgR += curR;
            images[index].avgG += curG;
            images[index].avgB += curB;
            ticker++;
        }
    }
    images[index].avgR = (images[index].avgR/(ticker + 0.0));
    images[index].avgG = (images[index].avgG/(ticker + 0.0));
    images[index].avgB = (images[index].avgB/(ticker + 0.0));
    if ( ((maxR-minR) < MAX_DIFF) || ((maxB-minB) < MAX_DIFF) || ((maxG-minG) < MAX_DIFF) )
        return true;
    else
        return false;
}
                           
// this goes through and generates all the colorgrids
// by calling the individual colorgrid creator
void createGrids(Bridges* bridges) {
    for (int i = 0; FILE_COUNT > i; i++) {
        createGrid(bridges, i);
    }
}

// displays whatever images[index].cg colour grid selected by the index provided.
void display2(Bridges* bridges, int index) {
    //bridges->setTitle("M6.3");
    bridges->setDataStructure(images[index].cg);
    //bridges->
    bridges->visualize();
}




int main(int argc, char **argv) {
    // create bridges object
    //new Bridges(4, "walmartgardner", "1057152140079");
    FILE_COUNT = 1;
  
    // used if providing multiuple files
    string files[] = {
        "/Users/lucas/Projects/2019Fall/ITSC3112/M6/M6/mickey_mouse.ppm"
    };
    
    string file1s[] = {
        "/Users/lucas/Projects/2019Fall/ITSC3112/M6/M6/me.ppm"
    };
    
    
    images = new Image[FILE_COUNT];
    //for (int i = 0; FILE_COUNT > i; i++) {
        //Image[i] = Image();
    //}
    
    for (int i = 0; FILE_COUNT > i; i++) {
        readFile(files[i], i);
        images[i].printDemims();
    }
    

    
    Bridges *bridges = new Bridges(6, "walmartgardner",
                     "1057152140079");
    
    createGrids(bridges);
    display2(bridges, 0);
    cout << "aaa\n";
    int s[] = {0, 0, images[0].dimensionX, images[0].dimensionY};
    KdTreeElement<int, int> *x = buildImageTree(0, s, 1, true);
    display2(bridges, 0);
    //display2(bridges, 1);
    
    
    return 0;
}
