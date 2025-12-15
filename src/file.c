#include <stdio.h>
#include <stdlib.h>
#include "../includes/file.h"

FileBuffer read_file(const char *path)
{
    FileBuffer buf;
    buf.data = NULL;
    buf.size = 0;

    FILE *f = fopen(path, "rb");
    if (f == NULL)
    {
        return buf;
    }

    fseek(f, 0, SEEK_END);
    buf.size = ftell(f);
    rewind(f);

    buf.data = malloc(buf.size);
    if (buf.data == NULL)
    {
        fclose(f);
        return buf;
    }

    size_t n = fread(buf.data, 1, buf.size, f);
    if (n != buf.size)
    {
        free_file_buffer(&buf);
        fclose(f);
        return buf;
    }

    fclose(f);

    return buf;
}

void free_file_buffer(FileBuffer *buf)
{
    free(buf->data);
    buf->data = NULL;
    buf->size = 0;
}
