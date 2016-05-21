/*
 * Write a method to decide if two strings are anagrams or not.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_anagram(const char *str1, const char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int ret = 0;

    if (len1 != len2)
        return 0;

    char *tmp_str = (char *)malloc(len1 * 2);
    if (tmp_str == NULL)
        return 0;
    memset(tmp_str, 0, len1 * 2);

    strncpy(tmp_str, str1, len1);
    strncpy(tmp_str + len1, str1, len1);

    int i;

    for (i = 0; i < len1 * 2; i++) {
        if (tmp_str[i] == str2[0])
        {
            if (strncmp(&tmp_str[i], str2, len2) == 0)
                ret = 1;
        }
    }

    free(tmp_str);

    return ret;
}

int main(int argc, char *argv[])
{
    char test_str1[] = "abcdefg";
    char test_str2[] = "efgabcd";

    printf("the result is %d\n", is_anagram(test_str1, test_str2));

    char test_str3[] = "1234567890";
    char test_str4[] = "2345678901";

    printf("the result is %d\n", is_anagram(test_str3, test_str4));

    return 0;
}
