#include <stdio.h>
#include "sort.h"

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



