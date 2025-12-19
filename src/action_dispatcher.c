#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/action_dispatcher.h"
#include "../includes/actions.h"

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
        printf("L'action %s est inconnue", action->name);
        return disaction;
    }

    return disaction;
}
