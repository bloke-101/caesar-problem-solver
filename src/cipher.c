#include <stdio.h>
#include <string.h>

#include <utils.h>
#include "frequency_analyzer.h"


void ShiftLowerCaseLetterToRight(char in, char* out, int shift) {
    *out = in + shift <= 'z' ? in + shift : in + shift - 26;    
}

void ShiftLowerCaseLetterToLeft(char in, char* out, int shift) {
    *out = in - shift >= 'a' ? in - shift : in - shift + 26;  
}

void ShiftUpperCaseLetterToRight(char in, char* out, int shift) {
    *out = in + shift <= 'Z' ? in + shift : in + shift - 26;
}

void ShiftUpperCaseLetterToLeft(char in, char* out, int shift) {
    *out = in - shift >= 'A' ? in - shift : in - shift + 26;  
}

void Encrypt(char* in, char* out, int shift) {
    int BLOCK_SIZE = 257;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (IsLowerCaseLetter(in[i])) {
            ShiftLowerCaseLetterToRight(in[i], &out[i], shift);
        }
        else if (IsUpperCaseLetter(in[i])) {
            ShiftUpperCaseLetterToRight(in[i], &out[i], shift);
        }
        else {
            out[i] = in[i];
        }
    }
}

int EncryptFile(FILE* in, FILE* out, int shift) {
    int BLOCK_SIZE = 257;
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

void Decrypt(char* in, char* out, int shift) {
    int BLOCK_SIZE = 257;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (IsLowerCaseLetter(in[i])) {
            ShiftLowerCaseLetterToLeft(in[i], &out[i], shift);
        }
        else if (IsUpperCaseLetter(in[i])) {
            ShiftUpperCaseLetterToLeft(in[i], &out[i], shift);
        }
        else {
            out[i] = in[i];
        }
    }    
}

int DecryptFile(FILE* in, FILE* out, int shift) {
    if (shift == -1 && FindShift(in, &shift) == -1) {
        return -1;
    }
    int BLOCK_SIZE = 257;
    char cipherntext[BLOCK_SIZE];
    char plaintext[BLOCK_SIZE];
    while (fgets(cipherntext, BLOCK_SIZE, in)) {
        Decrypt(cipherntext, plaintext, shift);
        if (fputs(plaintext, out) == -1) {
            perror("Failed to write a decrypted line");
            return -1;
        }
    }
    if (ferror(in)) {
        perror("Failed to read a ciphertext line");
        return -1;
    }
    return 0;
}
