#include <stdio.h>
#include "args.h"
#include "file.h"
#include "actions.h"
#include "action_dispatcher.h"
#include "format_dispatcher.h"
#include "errors.h"

int main(int argc, char **argv)
{
    // Initialisation de la structure Arguments
    Arguments args = parse_args(argc, argv);

    // Retourne 1 si la structure comporte une erreur
    if (args.has_error)
    {
        return 1;
    }

    // Lecture du fichier
    FileBuffer buf = read_file(args.input_file);
    if (buf.data == NULL)
    {
        return 1;
    }

    // Décodage du fichier
    buf = dispatch_format_decode(&buf, &args);

    FileBuffer current = buf;

    // Modification du fichier
    for (int i = 0; i < args.actions_count; i++)
    {
        FileBuffer new = dispatch_action(&current, &args.actions[i]);

        if (new.data == NULL || new.size == 0)
        {
            free_file_buffer(&current);
            return 1;
        }

        if (i > 0)
        {
            free_file_buffer(&current);
        }
        current = new;
    }

    // Encodage du fichier
    current = dispatch_format_encode(&current, &args);

    // Ecriture sur le disque
    write_file(args.output_file, &current);

    // Libération de la mémoire
    free_file_buffer(&current);

    return 0;
}