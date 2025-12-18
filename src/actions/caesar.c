#include <stdio.h>
#include <stdlib.h>

#include "../../includes/actions.h"

/**
 * \brief Permet d'appliquer un chiffrement de César au buffer.
 *
 * La clé est extraite du paramètre action->key et convertie en nombre.
 *
 * \param input_buffer Pointeur vers le buffer d'entrée contenant les données du fichier
 * \param action Pointeur vers la structure Action contenant la clé du décalage
 * \return Retourne un buffer avec les données transformées
 */
FileBuffer caesar(const FileBuffer *input_buffer, const Action *action)
{
    FileBuffer temp;
    temp.data = NULL;
    temp.size = 0;

    // Vérification des paramètres requis
    if (!input_buffer || !input_buffer->data || input_buffer->size == 0)
    {
        return temp;
    }

    if (!action || !action->key)
    {
        return temp;
    }

    // Récupération de la clé
    unsigned char key = (unsigned char)atoi(action->key);

    // Allocation de la mémoire
    temp.size = input_buffer->size;
    temp.data = malloc(temp.size + 1);
    if (!temp.data)
    {
        temp.size = 0;
        return temp;
    }

    // Appliquer le décalage à chaque charactère
    for (size_t i = 0; i < input_buffer->size; i++)
    {
        temp.data[i] = input_buffer->data[i] + key;
    }

    temp.data[temp.size] = '\0';

    return temp;
}