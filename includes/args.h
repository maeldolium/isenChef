#ifndef ARGS_H
#define ARGS_H

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
    char *name;
    void (*handler)(Arguments *, int *, int, char **);
} ArgHandler;

Arguments parse_args(int argc, char **argv);

#endif
