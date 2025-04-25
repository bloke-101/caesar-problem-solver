#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "cipher.h"
#include "string_utils.h"
#include "file_system_utils.h"
#include "frequency_analyzer.h"


static void shift_lower_case_letter(char in, char* out, int shift) {
    shift += in - 'a';
    *out = 'a' + (shift % alphabet_size + alphabet_size) % alphabet_size;
}

static void shift_upper_case_letter(char in, char* out, int shift) {
    shift += in - 'A';
    *out = 'A' + (shift % alphabet_size + alphabet_size) % alphabet_size;
}

static void shift_letters(char* in, char* out, int shift) {
    for (int i = 0; i < block_size; i++) {
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
    char input_line[block_size];
    char output_line[block_size];
    while (fgets(input_line, block_size, in)) {
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

