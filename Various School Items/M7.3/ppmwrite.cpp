/*
Created by Zowie Haugaard
9/16/16
PPM Converter
  This program is used to convert between the ascii and binary versions of the
  .ppm image file format.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "ppmwrite.hpp"

#define SIZE 256

using namespace std;
//using namespace bridges;

/**
 * RGBPix
 *
 * struct used as a representation of a single RGB pixel
 *
 * @param r pixel value of red
 * @param g pixel value of green
 * @param b pixel value of blue
 *
 */
//represents a single pixel object
typedef struct RGB {
  unsigned char r, g, b;
}RGBPix;


/**
 * PPMImage
 *
 * struct used to represent an image's data set.
 *
 * @param width  int value of width
 * @param height int value of height
 * @param data  RGBPix data set
 *
 */
//this struct is used to store the entire image data, along with the width and height
typedef struct Image {
  int width, height;
  RGBPix *data;
}PPMImage;

/**
 * ppmwrite
 *
 * [???]
 *
 * @param inFile  Input path of the file passed by main::Image generateText(string)
 * @param outFile Output path of the file passed by main::Image generateText(string)
 *
 */
//write a p3 file
void ppmwrite::writeP3 (FILE *inFile, FILE *outFile){

  //buffer used for the comments mainly
  char buff[SIZE], *fh;

  PPMImage image;

  int read, i, j, counter = 1;
  unsigned int maxColors;


  fh = (char *)malloc(sizeof(char) * SIZE);
  fh = fgets(buff, SIZE, inFile);             //Make sure we are reading the right type of file
  if ( (fh == NULL) || ( strncmp(buff, "P6\n", 3) != 0 ) ) perror("Please provide a P6 .ppm file for conversion\n");
  (void) fprintf(outFile, "P3\n");

  //get rid of comments
  do
        {
           fh = fgets(buff, SIZE, inFile);      //write the comments into the out file
           if( strncmp(buff, "#", 1) == 0) fprintf(outFile, "%s", buff);
           if ( fh == NULL ) return;
        } while ( strncmp(buff, "#", 1) == 0 );

  //read in the width and height
  read = sscanf(buff, "%u %u", &image.width, &image.height);


  //throw error if the width and height aren't in the file
  if(read < 2) {
    perror("File Unreadable. Please check the file format\n");
    return;
  }
  image.data = (RGBPix *)malloc(sizeof(RGBPix) * image.width * image.height);

  read = fscanf(inFile, "%u", &maxColors);
  //check that the right color format is used
  if(maxColors != 255 || read != 1) {
    perror("Please provide an 24-bit color file");
    return;
  }


  //put all that good stuff into the outFile
  fprintf(outFile, "%u %u\n%u\n",image.width, image.height, maxColors);

  //read the image into the buffer
  fread(image.data, sizeof(RGBPix), image.width * image.height, inFile);

  //write out to the ascii file
  for (i = 0; i < image.width * image.height; i++)
  {
      fprintf(outFile, " %d %d %d ", image.data[i].g, image.data[i].b, image.data[i].r);

      //format handling
      if(counter == image.width) {
        fprintf(outFile, "\n");
        counter = 1;
      }
      else counter += 1;
    }

}
