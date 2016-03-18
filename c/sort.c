#include <stdio.h>

void exchange(int *a, int *b)
{
    int tem;

    tem = *a;
    *a = *b;
    *b = tem;
}

void bubble(int array[], int size)
{
    int i, j;
    int tmp = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1; j++) {
            if (array[j] > array[j+1]) {
                tem = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tem;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int array1[10] = {7, 4, 1, 2, 5, 8, 9, 6, 3, 0};

    bubble(array1, 10);

    return 0;
}
