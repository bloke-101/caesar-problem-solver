#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "frequency_analyzer.h"
#include "string_utils.h"
#include "file_system_utils.h"

static void count_letters(char* text_line, unsigned* letter_count) 
{
    for (size_t i = 0; i < strlen(text_line); i++) 
    {
        if (is_lower_case_letter(text_line[i])) 
        {
            letter_count[text_line[i] - 'a']++;
        }
        else if (is_upper_case_letter(text_line[i])) 
        {
            letter_count[text_line[i] - 'A']++;
        }
    }
}

static int find_most_frequent_letter(unsigned* letter_count) 
{
    unsigned max = 0;
    int idx;
    for (int i = 0; i < alphabet_size; i++) 
    {
        if (letter_count[i] > max) 
        {
            max = letter_count[i];
            idx = i;
        }
    }
    return 'a' + idx;
}

int find_shift(FILE* in, int* shift) 
{
    unsigned letter_count[alphabet_size];
    memset(letter_count, 0, alphabet_size * sizeof(unsigned));
    char text_line[block_size];
    while (fgets(text_line, block_size, in)) 
    {
        count_letters(text_line, letter_count);
    }
    if (ferror(in)) 
    {
        perror("Failed to read a ciphertext line");
        return -1;
    }
    int i = find_most_frequent_letter(letter_count);
    *shift = ((i - 'e') % alphabet_size + alphabet_size) % alphabet_size;
    return reset_file_position(in);
}

