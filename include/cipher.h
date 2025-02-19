#include <stdio.h>


int IsLowerCaseLetter(char c);

int IsUpperCaseLetter(char c);

void ShiftLowerCaseLetterToRight(char in, char* out, int shift);

void ShiftLowerCaseLetterToLeft(char in, char* out, int shift);

void ShiftUpperCaseLetterToRight(char in, char* out, int shift);

void ShiftUpperCaseLetterToLeft(char in, char* out, int shift);

void Encrypt(char* in, char* out, int shift);

int EncryptFile(FILE* in, FILE* out, int shift);

void Decrypt(char* in, char* out, int shift);

int DecryptFile(FILE* in, FILE* out, int shift);
