#include <stdio.h>
#include <stdlib.h>

#include "../../includes/actions.h"

/**
 * \brief Permet de transformer le contenu d'un buffer en caractères hexadécimaux
 *
 * La fonction to_hex prend un buffer d'entrée et le transforme en représentation
 * hexadécimale. Chaque byte est converti en 2 caractères hexadécimaux.
 *
 * \param input_buffer Pointeur vers le buffer d'entrée contenant les données du fichier
 * \param action Pointeur vers la structure Action (inutilisée ici)
 * \return Retourne un buffer avec les données transformées, retourne
 * un buffer vide en cas d'erreur
 */
FileBuffer to_hex(const FileBuffer *input_buffer, const Action *action)
{
    FileBuffer temp;
    temp.data = NULL;
    temp.size = 0;

    // Vérification des paramètres requis
    if (!input_buffer || !input_buffer->data || input_buffer->size == 0)
    {
        return temp;
    }

    temp.size = input_buffer->size * 2;
    temp.data = malloc(temp.size + 1);
    if (!temp.data)
    {
        temp.size = 0;
        return temp;
    }

    for (size_t i = 0; i < input_buffer->size; i++)
    {
        sprintf((char *)&temp.data[i * 2], "%02X", (unsigned char)input_buffer->data[i]);
    }

    temp.data[temp.size] = '\0';

    return temp;
}