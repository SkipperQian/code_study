#include <stdio.h>
#include "sort.h"

void display_array(int array[], int size)
{
    int i;

    for (i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

static void exchange(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void sort_bubble(int array[], int size)
{
    int i, j;

    for (i = 0; i < size - 1; i++) {
        for (j = size - 1; j > i ; j--) {
            if (array[j] < array[j - 1]) {
                exchange(&array[j], &array[j - 1]);
            }
        }
    }
}

void sort_select(int array[], int size)
{
    int i, j;
    int key_index;

    for (i = 0; i < size - 1; i++) {
        key_index = i;
        for (j = i + 1; j < size; j++) {
            if (array[j] < array[key_index]) {
                key_index = j;
            }
        }

        if (i != key_index) 
            exchange(&array[key_index], &array[i]);
    }
}

void sort_quick(int array[], int low, int high)
{
    int i, j;
    int key;

    if (low >= high)
        return;

    i = low;
    j = high;
    key = array[low];

    while(i < j) {
        while (i < j && array[j] >= key)
            j--;
        exchange(&array[i], &array[j]);

        while(i < j && array[i] < key)
            i++;
        exchange(&array[i], &array[j]);
    }

    sort_quick(array, low, j - 1);
    sort_quick(array, i + 1, high);
}
