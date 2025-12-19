#ifndef ACTIONS_H
#define ACTIONS_H

#include "file.h"
#include "args.h"

FileBuffer to_uppercase(const FileBuffer *input_buffer, const Action *action);

FileBuffer to_lowercase(const FileBuffer *input_buffer, const Action *action);

FileBuffer caesar(const FileBuffer *input_buffer, const Action *action);

FileBuffer rc4(const FileBuffer *input_buffer, const Action *action);

FileBuffer xor (const FileBuffer *input_buffer, const Action *action);

#endif