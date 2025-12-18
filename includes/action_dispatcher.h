#ifndef ACTION_DISPATCHER_H
#define ACTION_DISPATCHER_H

#include "args.h"
#include "file.h"

typedef FileBuffer (*ActionFn)(const FileBuffer *, const Action *);

typedef struct
{
    const char *name;
    ActionFn fn;
} ActionEntry;

FileBuffer dispatch_action(const FileBuffer *input, const Action *action);

#endif