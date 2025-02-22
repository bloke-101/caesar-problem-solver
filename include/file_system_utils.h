#define BLOCK_SIZE 257

int OpenFile(FILE** f, char* filepath, char* mode);

int CloseFile(FILE** f, char* filepath);

int ResetFilePosition(FILE* in);
