#include <string.h>
#include "../includes/args.h"
#include "../includes/args_handlers.h"

/**
 *
 * \brief La fonction parse_args permet de parcourir la
 * ligne de commande entrée par l'utilisateur afin de stocker
 * les arguments de celle-ci.
 *
 * La fonction parse_args créer une variable args du type sturct
 * Arguments et l'initialise. Ensuite elle définit un tableau de structure
 * ArgHandler handlers contenant les arguments possible et la fonction qu'ils appellent.
 * Elle va ensuite parcourir la ligne de commande pour chercher une correspondance
 * entre l'argument actuelle et le tableau de structures des arguments et appeler la
 * fonction associée si l'argument existe.
 *
 * \param argc Nombre d'argument de la ligne de commande
 * \param argv Valeur de l'agument de la ligne de commande
 * \return Retourne la variable args
 */
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
