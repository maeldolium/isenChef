#ifndef ARGS_HANDLERS_H
#define ARGS_HANDLERS_H

#include "args.h"

void handle_in(Arguments *args, int *i, int argc, char **argv);

void handle_out(Arguments *args, int *i, int argc, char **argv);

void handle_action(Arguments *args, int *i, int argc, char **argv);

void handle_key(Arguments *args, int *i, int argc, char **argv);

void handle_input_format(Arguments *args, int *i, int argc, char **argv);

void handle_output_format(Arguments *args, int *i, int argc, char **arg);

int is_number(const char *str);

#endif
