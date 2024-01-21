/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"



Color *validPixel(Image *image, int row, int col, int i, int j){
    int rows = image->rows;
    int cols = image->cols;
    if (((row+i) < rows && (row+i) >= 0) && ((col+j) < cols && (col+j) >= 0))
        return image->image[((row+i)* cols) + (col+j)];
    return NULL;
}


//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE

    int rows = image->rows;
    int cols = image->cols;

    Color *cell = image->image[(row*cols) + col];

    int x[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int y[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int numOfLive[24] = { 0 };

    Color *neighbor;
    uint8_t rgb[3];
    for (int i = 0; i < 8; i++){
        if (neighbor = validPixel(image, row, col, x[i], y[i])){
            rgb[0] = neighbor->R;
            rgb[1] = neighbor->G;
            rgb[2] = neighbor->B;
            for (int b = 0; b < 3; b++){
                for (int h = 0; h < 8; h++){
                    if((rgb[b] >> h) & 1)
                        numOfLive[(b*8)+h]++;
                }
            }
        }
    }

   // for (int i = 0; i < 24; i++){
   //     printf("%d\n", numOfLive[i]);
   // }

    uint16_t offset;
    uint8_t orig_rgb[3] = {cell->R, cell->G, cell->B};
    uint8_t result_rgb[3] = {0};
    for (int b = 0; b < 3; b++){
        for (int h = 0; h < 8; h++){
            offset = 1;
            // is cell alive
            if ((orig_rgb[b] >> h) & 1)
                offset = offset << 9;

            offset = offset << numOfLive[(b*8)+h];

            // is it match the rule
            if (rule & offset)
                result_rgb[b] = result_rgb[b] | (1 << h);
        }
    }

    Color *result = (Color*) malloc(sizeof(Color));
    //printf("%d %d %d\n", result_rgb[0], result_rgb[0], result_rgb[0]);
    result->R = result_rgb[0];
    result->G = result_rgb[1];
    result->B = result_rgb[2];
    return result;

  //  // for top row and bottom row
  //  for (int i = row-1; i < row+2; i += 2){
  //      for (int j = col-1; j < col+2; j++){
  //          if ((i < rows && i >= 0) && (j < cols && j >= 0))
  //              if (stateOfCell(image->image[(i*cols)+j]))
  //                  numOfLive = numOfLive << 1;
  //      }
  //  }

  //  // for cell of left collumn and right 
  //  for (int j = col-1; j < col+2; j += 2){
  //      if (j < cols && j >= 0)
  //          if (stateOfCell(image->image[(row*cols)+j]))
  //              numOfLive = numOfLive << 1;
  //  }

  //  Color *result = (Color*) malloc(sizeof(Color));

  //  if (rule & numOfLive){
  //      result->R = 255;
  //      result->G = 255;
  //      result->B = 255;
  //      return result;
  //  }
  //  result->R = 0;
  //  result->G = 0;
  //  result->B = 0;
  //  return result;

}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
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
            color = evaluateOneCell(image, i, j, rule);
            new_image->image[(i*cols)+j] = color;
        }
    }

    return new_image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE

    if (argc != 3)
        printf("Usage: ./gameOfLife filename rule\nfilename is an ASCII PPM file (type P3) with maximum calue 255.\nrule is a hex number beginning with 0x; Life is 0x1808.");

    uint32_t rule = strtol(argv[2], NULL, 0);

    char *filename = argv[1];
    Image *input_image = readData(filename);

    Image *new_image = life(input_image, rule);
    writeData(new_image);

    freeImage(input_image);
    freeImage(new_image);
}
