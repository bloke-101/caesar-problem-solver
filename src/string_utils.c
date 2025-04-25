#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "string_utils.h"

int is_lower_case_letter(char c) {
    return c >= 'a' && c <= 'z';
}

int is_upper_case_letter(char c) {
    return c >= 'A' && c <= 'Z';
}

int convert_str_to_int(char* str, int* shift) {
    if (sscanf(str, "%d", shift) != 1) {
        char* msg = "Failed to convert '%s' to int\n";
        fprintf(stderr, msg, str);
        return -1;
    }
    return 0;
}

