#ifndef ARGS_H
#define ARGS_H

#include "../includes/args_handlers.h"

typedef struct
{
    char *name;
    char *key;
} Action;

typedef struct
{
    char *input_file;
    char *output_file;
    char *input_format;
    char *output_format;

    Action *actions;
    int actions_count;
    int has_error;
} Arguments;

typedef struct
{
    char *title;
    void (*action)(void);
} ArgumentListElement;

ArgumentListElement argsList[] = {
    {"--in", handle_in},
    {"--out", handle_out},
    {"--input-format", handle_input_format},
    {"--output-format", handle_output_format},
    {"--action", handle_action},
    {"--key", handle_key}};

Arguments parse_args(int argc, char **argv);

#endif
