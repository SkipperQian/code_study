/*
 * Design an algorithm and write code to remove the duplicate characters in a string
 * without using any additional buffer. NOTE: One or two additional variables are fine.
 * An extra copy of the array is not.
*/

#include <stdio.h>
#include <string.h>

void rm_duplicate_ch(char *str)
{
    if (str == NULL)
        return;

    int i, j;
    int len = strlen(str);
    int index = 0;

    for (i = 0; i < len; i++) {
        if (str[i] != 0) {
            str[index++] = str[i];

            for (j = i + 1; j < len; j++) {
                if (str[j] == str[i])
                    str[j] = 0;
            }
        }
    }
    str[index] = 0;
}

int main(int argc, char *argv[])
{
    char str1[20] = "aaabbcccc";
    char str2[20] = " hello world";

    rm_duplicate_ch(str1);
    printf("str1: %s\n", str1);

    rm_duplicate_ch(str2);
    printf("str2: %s\n", str2);
    return 0;
}
