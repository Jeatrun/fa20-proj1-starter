/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	
	//get the color** image
	Color ** p = image->image;

	//get the B value of the given pixel
	int currentIndex=row*image->cols+col;
	uint8_t blue=p[currentIndex]->B;
	
	//decode it 
	uint8_t LSB=blue&1;

	//create a new Color
	Color *newColor=malloc(sizeof(Color));
	if(LSB){
		newColor->R=255;
		newColor->G=255;
		newColor->B=255;
	}else{
		newColor->R=0;
		newColor->G=0;
		newColor->B=0;
	}
	return newColor;


}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	//create a new image
	Image *newImage=malloc(sizeof(Image));
	newImage->cols=image->cols;
	newImage->rows=image->rows;
	newImage->image=malloc(sizeof(Color*)*image->rows*image->cols);

	//access every pixels
	for(int i=0;i<image->rows;i++){
		for(int j=0;j<image->cols;j++){
			//evaluate the lsb 
			Color *newColor=malloc(sizeof(Color));
			newColor=evaluateOnePixel(image,i,j);
			//set the new color to the new image
			newImage->image[i*image->cols+j]=newColor;
		}


	}

	return newImage;

}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	//get the filename
	
	//read the file,get the image
	Image *image=readData(argv[1]);

	//evaluate the image,decode it,creat a new one
	Image *newImage=steganography(image);
	
	//print the new image out
	writeData(newImage);


	//free all memories
	freeImage(newImage);
	freeImage(image);
}
