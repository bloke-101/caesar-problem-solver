#include <stdio.h>
#include <string.h>

#include "utils.h"

const int ALPHABET_SIZE = 26;


void CountEnglishLetter(char* textline, unsigned int* amountOfLetters) {
    size_t len = strlen(textline);
    for (size_t i = 0; i < len; i++) {
        if (IsLowerCaseLetter(textline[i])) {
            amountOfLetters[textline[i] - 'a'];
        }
        else if (IsUpperCaseLetter(textline[i])) {
            amountOfLetters[textline[i] - 'A'];
        }
    }
}

void FindMostFrequentLetter(unsigned int* amountOfLetters, int* idx) {
    unsigned int max = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (amountOfLetters[i] > max) {
            max = amountOfLetters[i];
            *idx = i;
        }
    }
}

int FindShift(FILE* in, int* shift) {
    unsigned int amountOfLetters[ALPHABET_SIZE];
    memset(amountOfLetters, 0, ALPHABET_SIZE * sizeof(unsigned int));
    int BLOCK_SIZE = 257;
    char textline[BLOCK_SIZE];
    while (fgets(textline, BLOCK_SIZE, in)) {
        CountEnglishLetter(textline, amountOfLetters);
    }
    if (ferror(in)) {
        perror("Failed to read a ciphertext line");
        return -1;
    }
    int i;
    FindMostFrequentLetter(amountOfLetters, &i);
    *shift = 'a' + i - 'e' < 0 ? 'a' + i  - 'e' + 26 : 'a' + i - 'e'; 
    return 0;
}
