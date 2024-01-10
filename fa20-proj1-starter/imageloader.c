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
    Image *image = malloc(sizeof(Image));

    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("no such file\n");
        return image; 
    }
    
    char format[10], size[10];
    int cols, rows;
    fscanf(fp, "%s\n%d %d\n%s\n", format, &cols, &rows, size);

    image->cols = cols;
    image->rows = rows;
    
    Color **pixels = (Color**)malloc(sizeof(Color *) * cols * rows);
    int r, g, b;
    for (int i = 0; i < rows * cols; i++){
        fscanf(fp, "%3d %3d %3d", &r, &g, &b);
        Color* color = malloc(sizeof(Color));
        color->R = r;
        color->G = g;
        color->B = b;
        //Color color = {r, g, b};
        pixels[i] = color;
    }
    
    fclose(fp);

    image->image = pixels;

    return image;
    
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
    if (image == NULL){
        printf("image cannot be null\n");
        return;
    }

    int cols = image->cols;
    int rows = image->rows;

    printf("P3\n%d %d\n255\n", image->cols, image->rows);

    Color *color;
    int i;
    int j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols-1; j++){
            color = image->image[(i*cols) + j];
            printf("%3d %3d %3d   ", color->R, color->G, color->B);
        }
        color = image->image[(i*cols) + j];
        printf("%3d %3d %3d\n", color->R, color->G, color->B);
    }
}

//Frees an image
void freeImage(Image *image)
{
    int rows = image->rows;
    int cols = image->cols;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            free(image->image[(i*cols) + j]);
        }
    }
    free(image->image);
    free(image);
}
