#ifndef FILE_H
#define FILE_H

#include <stddef.h>

typedef struct
{
    unsigned char *data;
    size_t size;
} FileBuffer;

FileBuffer read_file(const char *path);

int write_file(const char *path, const FileBuffer *buf);

void free_file_buffer(FileBuffer *buf);

#endif