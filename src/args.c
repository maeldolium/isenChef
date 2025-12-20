#include "../includes/args.h"
#include "../includes/action_dispatcher.h"
#include "../includes/args_handlers.h"
#include "../includes/errors.h"
#include <string.h>

/**
 * \brief Permet de parcourir la ligne de commande pour stocker les arguments
 *
 * La fonction parse_args crée une variable args de type struct Arguments et
 * l'initialise. Elle définit un tableau de structures ArgHandler contenant les
 * arguments possibles et leurs fonctions de traitement. Elle parcourt ensuite
 * la ligne de commande pour chercher des correspondances avec le tableau des
 * arguments et appelle les fonctions associées si l'argument existe.
 *
 * \param argc Nombre d'arguments de la ligne de commande
 * \param argv Pointeur vers le tableau de pointeurs contenant les valeurs des
 * arguments
 * \return Retourne la structure Arguments contenant les paramètres parsés
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

    static ArgHandler handlers[] = {{"--in", handle_in},
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

    // Vérifie que toutes les actions qui demandent une clé en ont une
    for (int i = 0; i < args.actions_count; i++)
    {
        if (action_requires_key(args.actions[i].name) && args.actions[i].key == NULL)
        {
            print_error(ERR_MISSING_KEY, args.actions[i].name);
            args.has_error = 1;
            return args;
        }
    }

    return args;
}
/**
 * \brief Libère la mémoire allouée pour la structure Arguments
 *
 * La fonction free_arguments libère la mémoire allouée dynamiquement
 * pour le tableau des actions dans la structure Arguments et réinitialise
 * le compteur d'actions.
 *
 * \param args Pointeur vers la structure Arguments à libérer
 */
void free_arguments(Arguments *args)
{
    if (args == NULL)
        return;
    if (args->actions != NULL)
    {
        free(args->actions);
        args->actions = NULL;
    }
    args->actions_count = 0;
}