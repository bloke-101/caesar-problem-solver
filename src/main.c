#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "cipher.h"
#include "string_utils.h"
#include "file_system_utils.h"
#include "frequency_analyzer.h"

void show_help_msg() {
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

void show_incorrect_args_msg() {
    char* message = "Wrong CLI arguments!\n"
        "Read the help message.\n\n";
    fputs(message, stdout);
    show_help_msg();
}

int is_arg_in_range(int amount_of_args) {
    return amount_of_args >= 4 && amount_of_args <= 5;
}

int is_encryption_mode(char* mode) {
    return strcmp(mode, "-e") == 0;
}

int is_decryption_mode(char* mode) {
    return strcmp(mode, "-d") == 0;   
}

int is_supported_mode(char* mode) {
    return is_encryption_mode(mode) || is_decryption_mode(mode);
}

int is_shift_in_range(int shift) {
    return (shift == -1) || (shift >= 1 && shift <= 25);
}

int clean_up(FILE** in, char* in_file_path, FILE** out, char* out_file_path) {
    if (close_file(in, in_file_path) == -1) {
        if (close_file(out, out_file_path) == -1) {
            return -1;
        }
        return -1;
    }
    if (close_file(out, out_file_path) == -1) {
        return -1;
    }
    return 0;
}

int do_encryption(char* plaintext_path, char* ciphertext_path, int shift) {
    FILE* in = NULL;
    if (open_file(&in, plaintext_path, "r") == -1) {
        return -1;    
    }
    FILE* out = NULL;
    if (open_file(&out, ciphertext_path, "w") == -1) {
        clean_up(&in, plaintext_path, &out, ciphertext_path);
        return -1;    
    }
    if (shift_text(in, out, shift) == -1) {
        clean_up(&in, plaintext_path, &out, ciphertext_path);
        return -1;
    }
    if (clean_up(&in, plaintext_path, &out, ciphertext_path) == -1) {
        return -1;
    }
    char* msg = "Encrypted %s with shift=%d and saved it as %s\n"; 
    printf(msg, plaintext_path, shift, ciphertext_path);
    return 0;
}

int do_decryption(char* ciphertext_path, char* plaintext_path, int shift) {
    FILE* in = NULL;
    if (open_file(&in, ciphertext_path, "r") == -1) {
        return -1;    
    }
    if (shift == -1 && find_shift(in, &shift) == -1) {
        return -1;
    }
    FILE* out = NULL;
    if (open_file(&out, plaintext_path, "w") == -1) {
        clean_up(&in, ciphertext_path, &out, plaintext_path);
        return -1;    
    }
    if (shift_text(in, out, -shift) == -1) {
        clean_up(&in, ciphertext_path, &out, plaintext_path);
        return -1;
    }
    if (clean_up(&in, ciphertext_path, &out, plaintext_path) == -1) {
        return -1;
    }
    char* msg = "Decrypted %s with shift=%d and saved it as %s\n"; 
    printf(msg, ciphertext_path, shift, plaintext_path);
    return 0;
}

int main(int argc, char** argv) {
    if (!is_arg_in_range(argc)) {
        show_incorrect_args_msg();
        return 0;
    }
    int shift = -1;
    if (convert_str_to_int(argv[argc - 1], &shift) == -1) {
        return -1;
    } 
    if (!is_shift_in_range(shift)) {
        fprintf(stderr, "shift is out of range:%d\n", shift);
        return -1;
    }
    if (is_encryption_mode(argv[1]) && argc == 5) {
        return do_encryption(argv[2], argv[3], shift);
    }
    else if (is_decryption_mode(argv[1])) {
        return do_decryption(argv[2], argv[3], shift);
    }
    show_incorrect_args_msg();
    return 0;
}

