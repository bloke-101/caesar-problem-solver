#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "file_system_utils.h"

const int block_size = 257;

int open_file(FILE** f, char* file_path, char* mode) 
{
    *f = fopen(file_path, mode);
    if (!*f) 
    {
        char* msg = "Failed to open %s: %s\n";
        fprintf(stderr, msg, file_path, strerror(errno));
        return -1;
    }
    return 0;
}

int close_file(FILE** f, char* file_path) 
{
    if (!*f) 
    {
        int res = fclose(*f);
        if (res == EOF) 
        {
            char* msg = "Failed to close %s:%s\n";
            fprintf(stderr, msg, file_path, strerror(errno));
            return -1;
        }
        *f = NULL;
    }
    return 0;
}

int reset_file_position(FILE* in) 
{
    int res = fseek(in, 0, SEEK_SET);
    if (res) 
    {
        perror("Failed to reset file position");
        return -1;
    }
    return 0;
}

