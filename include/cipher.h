#include <stdio.h>


int IsLowerCaseLetter(char c);

int IsUpperCaseLetter(char c);

void ShiftLowerCaseLetter(char in, char* out, int shift);

void ShiftUpperCaseLetter(char in, char* out, int shift);

void Encrypt(char* in, char* out, int shift);

int EncryptFile(FILE* in, FILE* out, int shift);