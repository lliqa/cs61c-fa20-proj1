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

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
    int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};
    
    Color *p = (Color*)malloc(sizeof(Color));
    p->R = p->G = p->B = 0;

    for (int i = 0; i < 8; ++i) {
        int cr, cg, cb;
        cr = cg = cb = 0;
        for (int d = 0; d < 8; ++d) {
            int nr = row + dx[d], nc = col + dy[d];
            if (nr < 0) nr = image->rows - 1;
            if (nr >= image->rows) nr = 0;
            if (nc < 0) nc = image->cols - 1;
            if (nc >= image->cols) nc = 0;
        
            if (image->image[nr][nc].R & (1 << i)) ++cr;
            if (image->image[nr][nc].G & (1 << i)) ++cg;
            if (image->image[nr][nc].B & (1 << i)) ++cb;
        }
        if (rule & (1 << ((((image->image[row][col].R) >> i) & 1) * 9 + cr))) p->R += (1 << i);
        if (rule & (1 << ((((image->image[row][col].G) >> i) & 1) * 9 + cg))) p->G += (1 << i);
        if (rule & (1 << ((((image->image[row][col].B) >> i) & 1) * 9 + cb))) p->B += (1 << i);
    }
    return p;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
    Image *p = (Image*)malloc(sizeof(Image));
    p->rows = image->rows;
    p->cols = image->cols;
    p->image = (Color**)malloc(sizeof(Color*) * p->rows);
    for (int i = 0; i < p->rows; ++i) {
        p->image[i] = (Color*)malloc(sizeof(Color) * p->cols);
        for (int j = 0; j < p->cols; ++j) {
            Color *pt = evaluateOneCell(image, i, j, rule);
            p->image[i][j] = *pt;
            free(pt);
        }
    }
    return p;
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
    if (argc != 3) {
        printf ("usage: ./gameOfLife filename rule\n");
        printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
        printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
        return -1;
    }
    Image *p = readData(argv[1]);
    uint32_t rule = strtol(argv[2], '\0', 16);
    Image *np = life(p, rule);
    writeData(np);
    free(p);
    free(np);
    return 0;
}
