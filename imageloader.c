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
    FILE *fp = fopen(filename, "r");

    Image *p = (Image*)malloc(sizeof(Image));
    char buf[20];
    fscanf(fp, "%s", buf);
    fscanf(fp, "%u%u", &p->cols, &p->rows);
    uint32_t scale;
    fscanf(fp, "%u", &scale);
    p->image = (Color**)malloc(sizeof(Color*) * p->rows);
    for (int i = 0; i < p->rows; ++i) {
        p->image[i] = (Color*)malloc(sizeof(Color) * p->cols);

        for (int j = 0; j < p->cols; ++j)
            fscanf(fp, "%hhu%hhu%hhu", &p->image[i][j].R, &p->image[i][j].G, &p->image[i][j].B);
    }
    fclose(fp);
    return p;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
    printf("P3\n");
    printf("%u %u\n", image->cols, image->rows);
    printf("255\n");
    for (int i = 0; i < image->rows; ++i)
        for (int j = 0; j < image->cols; ++j) {
            printf("%3hhu %3hhu %3hhu", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
            if (j < image->cols - 1) printf("   ");
            else printf("\n");
        }
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
    for (int i = 0; i < image->rows; ++i) free(image->image[i]);
    free(image->image);
    free(image);
}