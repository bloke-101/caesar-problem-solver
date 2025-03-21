#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "string_utils.h"


int IsLowerCaseLetter(char c) {
    return c >= 'a' && c <= 'z';
}

int IsUpperCaseLetter(char c) {
    return c >= 'A' && c <= 'Z';
}

int ConvertStrToInt(char* str, int* shift) {
    if (sscanf(str, "%d", shift) != 1) {
        char* msg = "Failed to convert '%s' to int\n";
        fprintf(stderr, msg, str);
        return -1;
    }
    return 0;
}
