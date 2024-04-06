#define _CRT_SECURE_NO_WARNINGS 1
/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	
	
	//arguments of an image structure

	uint32_t colorbits;
	Image* img = (Image*)malloc(sizeof(Image));

	//open the file
	FILE *fp = fopen(filename,"r");

	//read the header
	fscanf(fp, "P3\n%"SCNu32" %"SCNu32"\n255\n",&img->cols,&img->rows);

	//create a 2D array of colors
	int totalpix = img->rows * img->cols;
	img->image = (Color**)malloc(sizeof(Color*) * totalpix);
	for (int i = 0; i < totalpix; i++) {
		*(img->image+i)= (Color*)malloc(sizeof(Color));
		Color* pixel = *(img->image + i);
		fscanf(fp, " %hhu  %hhu  %hhu   ", &pixel->R, &pixel->G, &pixel->B);
		

	}
	fclose(fp);

	return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	
	//print the header
	printf("P3\n%u %u\n255\n",image->cols,image->rows);
	//print the image data
	Color** p=image->image;
	for(int i=0;i<image->rows;i++)
	{
	    for(int j=0;j<image->cols-1;j++)
		{
			printf(" %hhu  %hhu  %hhu   ",(*p)->R,(*p)->G,(*p)->B);
			p++;
		}
		//print the last col with \n
		printf(" %hhu  %hhu  %hhu\n",(*p)->R,(*p)->G,(*p)->B);
		p++;
	}


}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	Color** p=image->image;
	//free the pointers of color** image
	for(int i=0;i<image->rows*image->cols;i++)
	{
	    
		free(*p);
		p++;
	}
	//free the color** image
	free(image->image);
	free(image);
}