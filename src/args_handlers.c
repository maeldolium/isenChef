#include <stdlib.h>
#include "../includes/args_handlers.h"

void handle_in(Arguments *args, int *i, int argc, char **argv)
{
    if (*i + 1 >= argc)
    {
        args->has_error = 1;
        return;
    }
    args->input_file = argv[*i + 1];
    (*i)++;
}

void handle_out(Arguments *args, int *i, int argc, char **argv)
{
    if (*i + 1 >= argc)
    {
        args->has_error = 1;
        return;
    }
    args->output_file = argv[*i + 1];
    (*i)++;
}

void handle_action(Arguments *args, int *i, int argc, char **argv)
{
    if (*i + 1 >= argc)
    {
        args->has_error = 1;
        return;
    }
    int next_index = args->actions_count;
    args->actions_count++;

    Action *new_tab = realloc(args->actions, args->actions_count * sizeof(Action));
    if (new_tab == NULL)
    {
        args->has_error = 1;
        return;
    }
    args->actions = new_tab;

    Action *action = &args->actions[next_index];
    action->name = argv[*i + 1];
    action->key = NULL;

    (*i)++;
}

void handle_key(Arguments *args, int *i, int argc, char **argv)
{
    if (args->actions_count == 0)
    {
        args->has_error = 1;
        return;
    }
    if (*i + 1 >= argc)
    {
        args->has_error = 1;
        return;
    }
    Action *last = &args->actions[args->actions_count - 1];
    last->key = argv[*i + 1];
    (*i)++;
}

void handle_input_format(Arguments *args, int *i, int argc, char **argv)
{
    if (*i + 1 >= argc)
    {
        args->has_error = 1;
        return;
    }
    args->input_format = argv[*i + 1];
    (*i)++;
}

void handle_output_format(Arguments *args, int *i, int argc, char **argv)
{
    if (*i + 1 >= argc)
    {
        args->has_error = 1;
        return;
    }
    args->output_format = argv[*i + 1];
    (*i)++;
}
