#include <stdio.h>


void ShowHelpMessage() {
    char* message = "Encrypt/decrypt text files with Caesar cipher.\n\n"
        
        "To perform encryption this tool needs:\n"
        "1. A plaintext file (in English).\n"
        "2. A key/shift (1-25).\n\n"
        
        "To perform decryption this tool needs:\n"
        "1. A ciphertext encrypted with Caesar cipher.\n"
        "2. A key/shift (1-25).\n\n"
        "If you don't have a key, but have a large ciphertext,"
        "frequency analysis can be carried out.\n\n"
        
        "Use-cases:\n"
        "1. caesar_problem_solver plaintext-path ciphertext-path key\n"
        "2. caesar_problem_solver ciphertext-path plaintext-path key\n"
        "3. caesar_problem_solver ciphertext-path plaintext-path\n\n"

        "Default values:\n"
        "1. ciphertext-path = ciphertext.txt\n"
        "2-3. plaintext-path = plaintext.txt\n";
    
    fputs(message, stdout);
}

int main(int argc, char** argv) {
    if (argc == 1) {
        ShowHelpMessage();
    }
    return 0;
}
