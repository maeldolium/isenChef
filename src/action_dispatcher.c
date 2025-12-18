#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/action_dispatcher.h"
#include "../includes/actions.h"

/**
 * \brief Permet d'associer à un nom d'action son appel de fonction.
 *
 * La fonction dispatch_action prend un buffer d'entrée input et une Action action.
 * Elle crée un buffer disaction et l'initialise. Ensuite, elle vérifie que input
 * et action existent, et crée un tableau de structures ActionsEntry qui associe
 * à chaque nom d'action sa fonction. Le programme cherche si le nom d'action
 * rentré par l'utilisateur existe et met le résultat de la transformation dans disaction.
 *
 * \param input Pointeur vers le buffer d'entrée contenant les données du fichier à modifier
 * \param action Pointeur vers la structure Action demandée par l'utilisateur
 * \return Retourne la structure FileBuffer contenant le résultat de la transformation
 */
FileBuffer dispatch_action(const FileBuffer *input, const Action *action)
{

    FileBuffer disaction;
    disaction.data = NULL;
    disaction.size = 0;

    // Vérification des paramètres requis
    if (!input || !input->data || input->size == 0)
    {
        return disaction;
    }

    if (!action || !action->name)
    {
        return disaction;
    }

    static ActionEntry actions[] = {
        {"uppercase", to_uppercase},
        {"lowercase", to_lowercase},
        {"hex", to_hex},
        {"base64", to_base64},
        {"caesar", caesar},
    };

    int actionsCount = sizeof(actions) / sizeof(actions[0]);

    int found = 0;

    for (int i = 0; i < actionsCount; i++)
    {
        if (strcmp(action->name, actions[i].name) == 0)
        {
            disaction = actions[i].fn(input, action);
            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("L'action %s est inconnue", action->name);
        return disaction;
    }

    return disaction;
}
