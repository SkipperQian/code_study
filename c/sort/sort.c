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
    int i = low, j = high;
    int key;

    if (low >= high)
        return;

    key = array[i];
    while(i < j) {
        while (i < j && array[j] >= key)
            j--;
        if (i < j) {
            array[i] = array[j];
            i++;
        }
        while(i < j && array[i] < key)
            i++;
        if (i < j) {
            array[j] = array[i];
            j--;
        }
    }
    array[i] = key;
    sort_quick(array, low, j - 1);
    sort_quick(array, i + 1, high);
}
