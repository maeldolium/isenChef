#include <string.h>
#include "../includes/args.h"
#include "../includes/args_handlers.h"

Arguments parse_args(int argc, char **argv)
{
    Arguments args;
    args.input_file = NULL;
    args.output_file = NULL;
    args.input_format = NULL;
    args.output_format = NULL;

    args.actions = NULL;
    args.actions_count = 0;

    args.has_error = 0;

    static ArgHandler handlers[] = {
        {"--in", handle_in},
        {"--out", handle_out},
        {"--input-format", handle_input_format},
        {"--output-format", handle_output_format},
        {"--action", handle_action},
        {"--key", handle_key}};

    int handlersCount = sizeof(handlers) / sizeof(handlers[0]);

    for (int i = 1; i < argc; i++)
    {
        int found = 0;
        for (int j = 0; j < handlersCount; j++)
        {
            if (strcmp(argv[i], handlers[j].name) == 0)
            {
                handlers[j].handler(&args, &i, argc, argv);
                if (args.has_error == 1)
                {
                    return args;
                }

                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            args.has_error = 1;
            return args;
        }
    }

    return args;
}
