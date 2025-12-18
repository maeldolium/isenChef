#ifndef ACTIONS_H
#define ACTIONS_H

#include "file.h"

FileBuffer to_uppercase(const FileBuffer *input_buffer);

FileBuffer to_lowercase(const FileBuffer *input_buffer);

FileBuffer to_hex(const FileBuffer *input_buffer);

FileBuffer to_base64(const FileBuffer *input_buffer);

#endif