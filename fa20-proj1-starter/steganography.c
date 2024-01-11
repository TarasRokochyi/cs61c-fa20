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

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE

    int tot_rows = image->rows;
    int tot_cols = image->cols;

    // getting blue color from (row*tot_cols)+col cell
    uint8_t blue = image->image[(row*tot_cols) + col]->B;

    uint8_t mask = 1;

    Color *color = (Color*) malloc(sizeof(Color));
    if (blue & mask){
        color->R = 255;
        color->G = 255;
        color->B = 255;
        return color;
    }
    else{
        color->R = 0;
        color->G = 0;
        color->B = 0;
        return color;
    }
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE

    int rows = image->rows;
    int cols = image->cols;

    Image *new_image = (Image*)malloc(sizeof(Image));
    new_image->image = (Color**)malloc(sizeof(Color *) * rows * cols);
    new_image->rows = rows;
    new_image->cols = cols;

    Color *color;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            color = evaluateOnePixel(image, i, j);
            new_image->image[(i*cols)+j] = color;
        }
    }

    return new_image;
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

    char *filename = argv[1];
    Image *input_image = readData(filename);

    Image *new_image = steganography(input_image);
    writeData(new_image);

    freeImage(input_image);
    freeImage(new_image);

}
