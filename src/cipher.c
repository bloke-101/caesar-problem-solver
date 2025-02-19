#include <stdio.h>
#include <string.h>

#include "cipher.h"

const unsigned int BLOCK_SIZE = 257;

int IsLowerCaseLetter(char c) {
    return c >= 'a' && c <= 'z';
}

int IsUpperCaseLetter(char c) {
    return c >= 'A' && c <= 'Z';
}

void ShiftLowerCaseLetter(char in, char* out, int shift) {
    *out = in + shift <= 'z' ? in + shift : in + shift - 26;    
}

void ShiftUpperCaseLetter(char in, char* out, int shift) {
    *out = in + shift <= 'Z' ? in + shift : in + shift - 26;
}

void Encrypt(char* in, char* out, int shift) {
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

int EncryptFile(FILE* in, FILE* out, int shift) {
    char plaintext[BLOCK_SIZE];
    char ciphertext[BLOCK_SIZE];
    while (fgets(plaintext, BLOCK_SIZE, in)) {
        Encrypt(plaintext, ciphertext, shift);
        if (fputs(ciphertext, out) == -1) {
            perror("Failed to write an encrypted line");
            return -1;
        }
    }
    if (ferror(in)) {
        perror("Failed to read a plaintext line");
        return -1;
    }
    return 0;
}
