/*
 * implement an algorithm to determine if a string has all unique characters.
 * What if you can not use additional data structures?
 */

#include <stdio.h>
#include <string.h>

int str_is_unique(char *str, int size)
{
    int tmp[256] = {0};
    int i = 0;

    for (i = 0; i < size; i++) {
        if (tmp[(int)str[i]] == 1)
            return 0;
        tmp[(int)str[i]] = 1;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    char str1[] = "abcdefghijklm";
    char str2[] = "zxcvbnmasdsazxcvbnm";
    char str3[] = "coding interviwe";

    printf("str1 is %d\n", str_is_unique(str1, strlen(str1)));
    printf("str2 is %d\n", str_is_unique(str2, strlen(str2)));
    printf("str3 is %d\n", str_is_unique(str3, strlen(str3)));
    return 0;
}
