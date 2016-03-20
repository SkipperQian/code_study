#include <stdio.h>

void display_array(int array[], int size)
{
    int i;

    for (i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void exchange(int *a, int *b)
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

int main(int argc, char *argv[])
{
    int array1[10] = {7, 4, 1, 2, 5, 8, 9, 6, 3, 0};
    int array2[10] = {7, 4, 1, 2, 5, 8, 9, 6, 3, 0};

    sort_bubble(array1, 10);
    display_array(array1, 10);

    sort_select(array2, 10);
    display_array(array2, 10);
    return 0;
}
