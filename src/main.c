#include "action_dispatcher.h"
#include "actions.h"
#include "args.h"
#include "errors.h"
#include "file.h"
#include "format_dispatcher.h"
#include <stdio.h>
#include <windows.h>

int main(int argc, char **argv)
{
    // Active le support UTF-8 sur Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    // Initialisation de la structure Arguments
    Arguments args = parse_args(argc, argv);

    // Retourne 0 si l'utilisateur a demandé l'aide
    if (args.help_requested)
    {
        free_arguments(&args);
        return 0;
    }

    // Retourne 1 si la structure comporte une erreur
    if (args.has_error)
    {
        free_arguments(&args);
        return 1;
    }

    // Lecture du fichier
    FileBuffer buf = read_file(args.input_file);
    if (buf.data == NULL)
    {
        free_arguments(&args);
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
            free_arguments(&args);
            return 1;
        }

        if (new.data != current.data)
        {
            free_file_buffer(&current);
        }
        current = new;
    }

    // Encodage du fichier
    FileBuffer temp = current;
    current = dispatch_format_encode(&current, &args);
    if (current.data != temp.data)
    {
        free(temp.data);
    }

    // Ecriture sur le disque
    write_file(args.output_file, &current);

    // Libération de la mémoire
    free_file_buffer(&current);
    free_arguments(&args);

    return 0;
}