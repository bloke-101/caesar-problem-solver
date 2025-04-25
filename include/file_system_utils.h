#ifndef FILE_SYSTEM_UTILS_H_SENTRY
#define FILE_SYSTEM_UTILS_H_SENTRY

extern const int block_size;

int open_file(FILE** f, char* file_path, char* mode);

int close_file(FILE** f, char* file_path);

int reset_file_position(FILE* in);

#endif

