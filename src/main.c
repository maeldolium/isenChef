#include <stdio.h>
#include "args.h"
#include "file.h"
#include "actions.h"
#include "action_dispatcher.h"
#include "format_dispatcher.h"

int main(int argc, char **argv)
{
    Arguments args = parse_args(argc, argv);

    FileBuffer buf = read_file(args.input_file);
    if (buf.data == NULL)
    {
        return 1;
    }

    buf = dispatch_format_decode(&buf, &args);

    FileBuffer current = buf;

    for (int i = 0; i < args.actions_count; i++)
    {
        FileBuffer new = dispatch_action(&current, &args.actions[i]);

        if (new.data == NULL || new.size == 0)
        {
            printf("Erreur lors de l'action %s.\n", args.actions[i].name);
            free_file_buffer(&current);
            return 1;
        }

        if (i > 0)
        {
            free_file_buffer(&current);
        }
        current = new;
    }

    current = dispatch_format_encode(&current, &args);

    write_file(args.output_file, &current);
    free_file_buffer(&current);

    return 0;
}