/*
 * Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, 
 * write a method to rotate the image by 90 degrees. Can you do this in place?
 *
 */

/* Solution:
 *
 * origin:
 *  1  2  3  4
 *  5  6  7  8
 *  9 10 11 12
 * 13 14 15 16
 *
 * step1:
 *  1  5  9 13
 *  2  6 10 14
 *  3  7 11 15
 *  4  8 12 16
 *
 * step2:
 *  4  8 12 16
 *  3  7 11 15
 *  2  6 10 14
 *  1  5  9 13
 */

#include <stdio.h>

void exchange(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void display(int array[][4], int row)
{
    int i, j;

    for (i = 0; i < row; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d, ", array[i][j]);
        }
        printf("\n");
    }
}

void rotate_matrix(int array[][4], int row)
{
    int i, j;

    //step 1
    for (i = 0; i < row; i++) {
        for (j = i + 1; j < row; j++) {
            exchange(&array[i][j], &array[j][i]);
        }
    }

    //step 2
    for (i = 0; i < row / 2; i++) {
        for (j = 0; j < row; j++) {
            exchange(&array[i][j], &array[row - 1 - i][j]);
        }
    }
}

int main(int argc, char *argv[])
{
    int matrix[4][4] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}};

    rotate_matrix(matrix, 4);
    display(matrix, 4);

    return 0;
}
