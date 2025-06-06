#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "string_utils.h"

const int alphabet_size = 26;

int is_lower_case_letter(char c) 
{
    return c >= 'a' && c <= 'z';
}

int is_upper_case_letter(char c) 
{
    return c >= 'A' && c <= 'Z';
}

int convert_str_to_int(char* str, int* shift) 
{
    int res = sscanf(str, "%d", shift);
    if (res != 1) 
    {
        char* msg = "Failed to convert '%s' to int\n";
        fprintf(stderr, msg, str);
        return -1;
    }
    return 0;
}

