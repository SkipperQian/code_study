/*
 * Write a method to replace all spaces in a string with ‘%20’.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int spaces_cnt(const char *str, int len)
{
    int i = 0;
    int cnt = 0;

    for (i = 0; i < len; i++) {
        if (str[i] == ' ')
            cnt++;
    }

    return cnt;
}

void replace_spaces(const char *input, char **output)
{
    int oldlen = strlen(input);
    int bufsize = 0;
    char *p = NULL;
    int i = 0;

    bufsize = spaces_cnt(input, oldlen) * 3 + oldlen + 1;
    p = (char *)malloc(bufsize);
    memset(p, 0, bufsize);

    *output = p;
    for (i = 0; i < oldlen; i++) {
        if (input[i] == ' ') {
            *(p++) = '%';
            *(p++) = '2';
            *(p++) = '0';
        } else {
            *p = input[i];
            p++;
        }
    }
}

int main(int argc, char *argv[])
{
    char test_str[] = "a b c d efg";
    char *new_str = NULL;

    replace_spaces(test_str, &new_str);
    printf("new str: %s\n", new_str);

    free(new_str);
    return 0;
}
