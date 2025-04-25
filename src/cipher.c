#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "cipher.h"
#include "string_utils.h"
#include "file_system_utils.h"
#include "frequency_analyzer.h"

void shift_lower_case_letter(char in, char* out, int shift) {
    shift += in - 'a';
    *out = 'a' + (shift % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
}

void shift_upper_case_letter(char in, char* out, int shift) {
    shift += in - 'A';
    *out = 'A' + (shift % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
}

void shift_letters(char* in, char* out, int shift) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (is_lower_case_letter(in[i])) {
            shift_lower_case_letter(in[i], &out[i], shift);
        }
        else if (is_upper_case_letter(in[i])) {
            shift_upper_case_letter(in[i], &out[i], shift);
        }
        else {
            out[i] = in[i];
        }
    }
}

int shift_text(FILE* in, FILE* out, int shift) {
    char input_line[BLOCK_SIZE];
    char output_line[BLOCK_SIZE];
    while (fgets(input_line, BLOCK_SIZE, in)) {
        shift_letters(input_line, output_line, shift);
        if (fputs(output_line, out) == -1) {
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

