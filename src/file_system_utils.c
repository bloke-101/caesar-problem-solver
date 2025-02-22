#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "file_system_utils.h"


int OpenFile(FILE** f, char* filepath, char* mode) {
    if ((*f = fopen(filepath, mode)) == NULL) {
        char* msg = "Failed to open %s: %s\n";
        fprintf(stderr, msg, filepath, strerror(errno));
        return -1;
    }
    return 0;
}

static int IsOpen(FILE* f) {
    return f != NULL;
}

int CloseFile(FILE** f, char* filepath) {
    if (!IsOpen(*f)) {
        return 0;
    }
    if (fclose(*f) == EOF) {
        char* msg = "Failed to close %s:%s\n";
        fprintf(stderr, msg, filepath, strerror(errno));
        return -1;
    }
    *f = NULL;
    return 0;
}

int ResetFilePosition(FILE* in) {
    if (fseek(in, 0, SEEK_SET) != 0) {
        perror("Failed to reset file position");
        return -1;
    }
    return 0;
}
