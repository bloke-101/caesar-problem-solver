#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "frequency_analyzer.h"
#include "string_utils.h"
#include "file_system_utils.h"

void count_english_letter(char* text_line, unsigned int* amount_of_letters) {
    size_t len = strlen(text_line);
    for (size_t i = 0; i < len; i++) {
        if (is_lower_case_letter(text_line[i])) {
            amount_of_letters[text_line[i] - 'a']++;
        }
        else if (is_upper_case_letter(text_line[i])) {
            amount_of_letters[text_line[i] - 'A']++;
        }
    }
}

void find_most_frequent_letter(unsigned int* amount_of_letters, int* idx) {
    unsigned int max = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (amount_of_letters[i] > max) {
            max = amount_of_letters[i];
            *idx = 'a' + i;
        }
    }
}

int find_shift(FILE* in, int* shift) {
    unsigned int amount_of_letters[ALPHABET_SIZE];
    memset(amount_of_letters, 0, ALPHABET_SIZE * sizeof(unsigned int));
    char text_line[BLOCK_SIZE];
    while (fgets(text_line, BLOCK_SIZE, in)) {
        count_english_letter(text_line, amount_of_letters);
    }
    if (ferror(in)) {
        perror("Failed to read a ciphertext line");
        return -1;
    }
    int i;
    find_most_frequent_letter(amount_of_letters, &i);
    *shift = ((i - 'e') % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
    if (reset_file_position(in) == -1) {
        return -1;
    } 
    return 0;
}
