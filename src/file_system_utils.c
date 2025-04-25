#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "file_system_utils.h"

const int block_size = 257;

int open_file(FILE** f, char* file_path, char* mode) {
    if ((*f = fopen(file_path, mode)) == NULL) {
        char* msg = "Failed to open %s: %s\n";
        fprintf(stderr, msg, file_path, strerror(errno));
        return -1;
    }
    return 0;
}

static int is_open(FILE* f) {
    return f != NULL;
}

int close_file(FILE** f, char* file_path) {
    if (!is_open(*f)) {
        return 0;
    }
    if (fclose(*f) == EOF) {
        char* msg = "Failed to close %s:%s\n";
        fprintf(stderr, msg, file_path, strerror(errno));
        return -1;
    }
    *f = NULL;
    return 0;
}

int reset_file_position(FILE* in) {
    if (fseek(in, 0, SEEK_SET) != 0) {
        perror("Failed to reset file position");
        return -1;
    }
    return 0;
}

