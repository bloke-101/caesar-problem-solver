#define BLOCK_SIZE 257

int open_file(FILE** f, char* file_path, char* mode);

int close_file(FILE** f, char* file_path);

int reset_file_position(FILE* in);

