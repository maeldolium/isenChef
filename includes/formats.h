#ifndef FORMATS_H
#define FORMATS_H

#include "file.h"

FileBuffer to_hex(const FileBuffer *input_buffer);

FileBuffer from_hex(const FileBuffer *input_buffer);

FileBuffer to_base64(const FileBuffer *input_buffer);

FileBuffer from_base64(const FileBuffer *input_buffer);

#endif