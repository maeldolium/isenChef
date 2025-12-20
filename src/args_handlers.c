#include <stdlib.h>

#include "../includes/action_dispatcher.h"
#include "../includes/args_handlers.h"
#include "../includes/errors.h"
#include "../includes/format_dispatcher.h"

/**
 *
 * \brief La fonction handle_in permet de stocker le fichier
 * d'entrée dans args.
 *
 * \param args Variable de type struc Arguments stockant les
 * arguments entrés par l'utilisateur
 * \param i Argument actuellement traité
 * \param argc Nombre d'argument de la ligne de commande
 * \param argv Valeur de l'argument de la ligne de commande
 * \return Retour vide en cas d'erreur pour arrêter l'exécution.
 */
void handle_in(Arguments *args, int *i, int argc, char **argv)
{
    if (*i + 1 >= argc || argv[*i + 1][0] == '-')
    {
        print_error(ERR_MISSING_ARGUMENT, "--in");
        args->has_error = 1;
        return;
    }
    args->input_file = argv[*i + 1];
    (*i)++;
}

/**
 *
 * \brief La fonction handle_out permet de stocker le fichier
 * de sortie dans args.
 *
 * \param args Variable de type struc Arguments stockant les
 * arguments entrés par l'utilisateur
 * \param i Argument actuellement traité
 * \param argc Nombre d'argument de la ligne de commande
 * \param argv Valeur de l'argument de la ligne de commande
 * \return Retour vide en cas d'erreur pour arrêter l'exécution.
 */
void handle_out(Arguments *args, int *i, int argc, char **argv)
{
    if (*i + 1 >= argc || argv[*i + 1][0] == '-')
    {
        print_error(ERR_MISSING_ARGUMENT, "--out");
        args->has_error = 1;
        return;
    }
    args->output_file = argv[*i + 1];
    (*i)++;
}

/**
 *
 * \brief La fonction handle_action permet de stocker l'action
 * entrée par l'utilisateur dans args. Elle peut être appelé plusieurs
 * fois si plusieurs actions demandées.
 *
 * \param args Variable de type struc Arguments stockant les
 * arguments entrés par l'utilisateur
 * \param i Argument actuellement traité
 * \param argc Nombre d'argument de la ligne de commande
 * \param argv Valeur de l'argument de la ligne de commande
 * \return Retour vide en cas d'erreur pour arrêter l'exécution.
 */
void handle_action(Arguments *args, int *i, int argc, char **argv)
{
    if (*i + 1 >= argc || argv[*i + 1][0] == '-')
    {
        print_error(ERR_MISSING_ARGUMENT, "--action");
        args->has_error = 1;
        return;
    }
    int next_index = args->actions_count;
    args->actions_count++;

    Action *new_tab = realloc(args->actions, args->actions_count * sizeof(Action));
    if (new_tab == NULL)
    {
        print_error(ERR_MEMORY_ALLOCATION, "actions list");
        args->has_error = 1;
        return;
    }
    args->actions = new_tab;

    Action *action = &args->actions[next_index];
    action->name = argv[*i + 1];
    action->key = NULL;

    // Vérifie que l'action est valide
    if (!is_valid_action(action->name))
    {
        print_error(ERR_UNKNOWN_ACTION, action->name);
        args->has_error = 1;
        return;
    }

    (*i)++;
}

/**
 *
 * \brief La fonction handle_key permet de stocker la clé
 * donnée par l'utilisateur dans args si l'action qui la précède en nécessite
 * une.
 *
 * \param args Variable de type struc Arguments stockant les
 * arguments entrés par l'utilisateur
 * \param i Argument actuellement traité
 * \param argc Nombre d'argument de la ligne de commande
 * \param argv Valeur de l'argument de la ligne de commande
 * \return Retour vide en cas d'erreur pour arrêter l'exécution.
 */
void handle_key(Arguments *args, int *i, int argc, char **argv)
{
    if (args->actions_count == 0)
    {
        print_error(ERR_MISSING_ARGUMENT, "--action");
        args->has_error = 1;
        return;
    }
    if (*i + 1 >= argc || argv[*i + 1][0] == '-')
    {
        print_error(ERR_MISSING_ARGUMENT, "--key");
        args->has_error = 1;
        return;
    }
    Action *last = &args->actions[args->actions_count - 1];
    last->key = argv[*i + 1];
    (*i)++;
}

/**
 *
 * \brief La fonction handle_in permet de stocker le format du fichier
 * d'entrée dans args.
 *
 * \param args Variable de type struc Arguments stockant les
 * arguments entrés par l'utilisateur
 * \param i Argument actuellement traité
 * \param argc Nombre d'argument de la ligne de commande
 * \param argv Valeur de l'argument de la ligne de commande
 * \return Retour vide en cas d'erreur pour arrêter l'exécution.
 */
void handle_input_format(Arguments *args, int *i, int argc, char **argv)
{
    if (*i + 1 >= argc || argv[*i + 1][0] == '-')
    {
        print_error(ERR_MISSING_ARGUMENT, "--input-format");
        args->has_error = 1;
        return;
    }

    // Vérifie que le format est valide
    if (!is_valid_format(argv[*i + 1]))
    {
        print_error(ERR_UNKNOWN_FORMAT, argv[*i + 1]);
        args->has_error = 1;
        return;
    }

    args->input_format = argv[*i + 1];
    (*i)++;
}

/**
 *
 * \brief La fonction handle_in permet de stocker le format du
 * fichier de sortie dans args.
 *
 * \param args Variable de type struc Arguments stockant les
 * arguments entrés par l'utilisateur
 * \param i Argument actuellement traité
 * \param argc Nombre d'argument de la ligne de commande
 * \param argv Valeur de l'argument de la ligne de commande
 * \return Retour vide en cas d'erreur pour arrêter l'exécution.
 */
void handle_output_format(Arguments *args, int *i, int argc, char **argv)
{
    if (*i + 1 >= argc || argv[*i + 1][0] == '-')
    {
        print_error(ERR_MISSING_ARGUMENT, "--output-format");
        args->has_error = 1;
        return;
    }

    // Vérifie que le format est valide
    if (!is_valid_format(argv[*i + 1]))
    {
        print_error(ERR_UNKNOWN_FORMAT, argv[*i + 1]);
        args->has_error = 1;
        return;
    }

    args->output_format = argv[*i + 1];
    (*i)++;
}
