#include <stdio.h>
#include <errno.h>
#include <string.h>


void ShowHelpMsg() {
    char* message = "Encrypt/decrypt text files with Caesar cipher.\n\n"

        "To perform encryption this tool needs:\n"
        "1. A plaintext file (in English).\n"
        "2. A key/shift (1-25).\n\n"
        
        "To perform decryption this tool needs:\n"
        "1. A ciphertext file.\n"
        "2. A key/shift (1-25).\n\n"
        
        "If you don't have a key, but have a large ciphertext,"
        "frequency analysis can be carried out.\n\n"
        
        "Use-cases:\n"
        "1. caesar_problem_solver -e plaintext-path ciphertext-path key\n"
        "2. caesar_problem_solver -d ciphertext-path plaintext-path key\n"
        "3. caesar_problem_solver -d ciphertext-path plaintext-path\n";
    
    fputs(message, stdout);
}

void ShowIncorrectArgsMsg() {
    char* message = "Incorrect the CLI arguments!\n"
        "Read the help message.\n\n";
    fputs(message, stdout);
    ShowHelpMsg();
}

int IsInRange(int* amountOfArgs) {
    return *amountOfArgs >= 4 && *amountOfArgs <= 5;
}

int IsEncryptionMode(char* mode) {
    return strcmp(mode, "-e") == 0;
}

int IsDecryptionMode(char* mode) {
    return strcmp(mode, "-d") == 0;   
}

int IsSupportedMode(char* mode) {
    return IsEncryptionMode(mode) || IsDecryptionMode(mode);
}

int ConvertStrToInt(char* str, int* shift) {
    if (sscanf(str, "%d", shift) != 1) {
        char* msg = "Failed to convert %s to int:%s\n";
        fprintf(stderr, msg, str, strerror(errno));
        return -1;
    }
    return 0;
}

int IsShiftInRange(int* shift) {
    return *shift > 0 && *shift <= 25;
}

int OpenFile(FILE** f, char* filepath, char* mode) {
    if ((*f = fopen(filepath, mode)) == NULL) {
        char* msg = "Failed to open %s: %s\n";
        fprintf(stderr, msg, filepath, strerror(errno));
        return -1;
    }
    return 0;
}

int CloseFile(FILE** f, char* filepath) {
    if (fclose(*f) == EOF) {
        char* msg = "Failed to close %s:%s\n";
        fprintf(stderr, msg, filepath, strerror(errno));
        return -1;
    }
    return 0;
}

int CleanUp(FILE** in, char* inFilepath, FILE** out, char* outFilepath) {
    if (CloseFile(in, inFilepath) == -1) {
        return -1;
    }
    if (CloseFile(out, outFilepath) == -1) {
        return -1;
    }
    return 0;
}

int DoEncryption(char* plaintextPath, char* ciphertextPath, int* shift) {
    if (!IsShiftInRange(shift)) {
        fprintf(stderr, "Shift is out of range:%d", *shift);
        return -1;
    }
    FILE* in;
    if (OpenFile(&in, plaintextPath, "r") == -1) {
        return -1;    
    }
    FILE* out;
    if (OpenFile(&out, ciphertextPath, "w") == -1) {
        return -1;    
    }
    printf("FILE ENCRYPTING\n");
    if (CleanUp(&in, plaintextPath, &out, ciphertextPath) == -1) {
        return -1;
    }
    return 0;
}

int DoDecryption(char* ciphertextPath, char* plaintextPath, int* shift) {
    FILE* in;
    if (OpenFile(&in, ciphertextPath, "r") == -1) {
        return -1;    
    }
    FILE* out;
    if (OpenFile(&out, plaintextPath, "w") == -1) {
        return -1;    
    }
    printf("FILE DECRYPTING\n");
    if (CleanUp(&in, plaintextPath, &out, ciphertextPath) == -1) {
        return -1;
    }
    return 0;
}

int main(int argc, char** argv) {
    if (!IsInRange(&argc) || !IsSupportedMode(argv[1])) {
        ShowIncorrectArgsMsg();
        return -1;
    }
    int shift = -1;
    if (IsDecryptionMode(argv[1]) && argc == 4) {
        return DoDecryption(argv[2], argv[3], &shift);
    }
    if (ConvertStrToInt(argv[argc - 1], &shift) == -1) {
        return -1;
    }
    if (!IsShiftInRange(&shift)) {
        fprintf(stderr, "Shift is out of range: %d\n", shift);
        return -1;
    }
    if (IsEncryptionMode(argv[1])) {
        return DoEncryption(argv[2], argv[3], &shift);
    }
    else if (IsDecryptionMode(argv[1])) {
        return DoDecryption(argv[2], argv[3], &shift);
    }
    return 0;
}
