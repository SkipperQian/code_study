#include <stdio.h>
#include <string.h>


void reversestr(char *str)
{
    if (str == NULL)
        return;

    int len = strlen(str);
    char *p = str;
    int i = 0;

    for (i = 0; i < len / 2; i++) {
        p[i] = p[len - i - 1] + p[i];
        p[len - i - 1] = p[i] - p[len - i - 1];
        p[i] = p[i] - p[len - i - 1];
    }
}


int main(int argc, char *argv[])
{
    char str1[100] = "hello world";
    char str2[100] = "abcdefg1234567";

    reversestr(str1);
    reversestr(str2);

    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);

    return 0;
}
