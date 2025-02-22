#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "cipher.h"
#include "string_utils.h"
#include "file_system_utils.h"
#include "frequency_analyzer.h"


void ShiftLowerCaseLetter(char in, char* out, int shift) {
    int offset = in - 'a' + shift;
    *out = 'a' + (offset % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
}

void ShiftUpperCaseLetter(char in, char* out, int shift) {
    int offset = in - 'A' + shift;
    *out = 'A' + (offset % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
}

void ShiftLetters(char* in, char* out, int shift) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (IsLowerCaseLetter(in[i])) {
            ShiftLowerCaseLetter(in[i], &out[i], shift);
        }
        else if (IsUpperCaseLetter(in[i])) {
            ShiftUpperCaseLetter(in[i], &out[i], shift);
        }
        else {
            out[i] = in[i];
        }
    }
}

int Shift(FILE* in, FILE* out, int shift) {
    char inputLine[BLOCK_SIZE];
    char outputLine[BLOCK_SIZE];
    while (fgets(inputLine, BLOCK_SIZE, in)) {
        ShiftLetters(inputLine, outputLine, shift);
        if (fputs(outputLine, out) == -1) {
            perror("Failed to write a line");
            return -1;
        }
    }
    if (ferror(in)) {
        perror("Failed to read a line");
        return -1;    
    }
    return 0;
}
