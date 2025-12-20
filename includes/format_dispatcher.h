#ifndef FORMAT_DISPATCHER_H
#define FORMAT_DISPATCHER_H

#include "file.h"
#include "args.h"

typedef FileBuffer (*FormatFn)(const FileBuffer *);

typedef struct
{
    const char *name;
    FormatFn encode;
    FormatFn decode;
} FormatEntry;

FileBuffer dispatch_format_decode(const FileBuffer *input_buffer, const Arguments *args);

FileBuffer dispatch_format_encode(const FileBuffer *input_buffer, const Arguments *args);

int is_valid_format(const char *format_name);

#endif