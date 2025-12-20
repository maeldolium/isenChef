#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/action_dispatcher.h"
#include "../includes/actions.h"
#include "../includes/errors.h"

/**
 * \brief Vérifie si une action demande une clé obligatoire
 *
 * La fonction action_requires_key retourne 1 si l'action spécifiée
 * nécessite une clé pour fonctionner.
 *
 * \param action_name Pointeur vers le nom de l'action à vérifier
 * \return Retourne 1 si l'action demande une clé, 0 sinon
 */
int action_requires_key(const char *action_name)
{
    if (!action_name)
        return 0;

    // Les actions qui demandent une clé
    const char *key_required[] = {
        "caesar",
        "RC4",
        "XOR"};

    int count = sizeof(key_required) / sizeof(key_required[0]);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(action_name, key_required[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * \brief Vérifie si une action donnée est valide
 *
 * La fonction is_valid_action vérifie si le nom d'action passé en paramètre
 * existe dans la liste des actions disponibles.
 *
 * \param action_name Pointeur vers le nom de l'action à vérifier
 * \return Retourne 1 si l'action est valide, 0 sinon
 */
int is_valid_action(const char *action_name)
{
    if (!action_name)
        return 0;

    // Tableau de structure des actions connues
    static ActionEntry actions[] = {
        {"uppercase", to_uppercase},
        {"lowercase", to_lowercase},
        {"caesar", caesar},
        {"RC4", rc4},
        {"XOR", xor},
    };

    int actionsCount = sizeof(actions) / sizeof(actions[0]);

    for (int i = 0; i < actionsCount; i++)
    {
        if (strcmp(action_name, actions[i].name) == 0)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * \brief Permet d'associer à un nom d'action son appel de fonction.
 *
 * La fonction dispatch_action prend un buffer d'entrée input_buffer et une Action action.
 * Elle crée un buffer disaction et l'initialise. Ensuite, elle vérifie que input_buffer
 * et action existent, et crée un tableau de structures ActionsEntry qui associe
 * à chaque nom d'action sa fonction. Le programme cherche si le nom d'action
 * rentré par l'utilisateur existe et met le résultat de la transformation dans disaction.
 *
 * \param input_buffer Pointeur vers le buffer d'entrée contenant les données du fichier à modifier
 * \param action Pointeur vers la structure Action demandée par l'utilisateur
 * \return Retourne la structure FileBuffer contenant le résultat de la transformation
 */
FileBuffer dispatch_action(const FileBuffer *input_buffer, const Action *action)
{

    FileBuffer disaction;
    disaction.data = NULL;
    disaction.size = 0;

    // Vérification des paramètres requis
    if (!input_buffer || !input_buffer->data || input_buffer->size == 0)
    {
        return disaction;
    }

    if (!action || !action->name)
    {
        return disaction;
    }

    // Tableau de structure des actions connues
    static ActionEntry actions[] = {
        {"uppercase", to_uppercase},
        {"lowercase", to_lowercase},
        {"caesar", caesar},
        {"RC4", rc4},
        {"XOR", xor},
    };

    int actionsCount = sizeof(actions) / sizeof(actions[0]);

    int found = 0;
    // Recherche le nom de l'action dans le tableau et l'applique
    // l'applique si elle existe
    for (int i = 0; i < actionsCount; i++)
    {
        if (strcmp(action->name, actions[i].name) == 0)
        {
            disaction = actions[i].fn(input_buffer, action);
            found = 1;
            break;
        }
    }

    // Sinon retourne une erreur et un buffer vide
    if (found == 0)
    {
        print_error(ERR_UNKNOWN_ACTION, action->name);
        fflush(stdout);
        return disaction;
    }

    return disaction;
}
