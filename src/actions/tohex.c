#include <stdio.h>
#include <stdlib.h>

#include "../../includes/actions.h"

/**
 *
 * \brief Permet de transformer le contenu d'un buffer en
 * caractère hexadécimal
 *
 * La fonction to_hex prend un buffer d'entrée input_buffer, puis crée
 * et initialise un buffer temporaire temp. Ensuite elle donne à temp le double de
 * la taille du buffer d'entrée + 1 (pour le \0) et transforme chaque caractère du
 * buffer d'entrée en 2 caractères hexadécimal et termine par \0.
 *
 * \param input_buffer Buffer d'entrée contenant les données du fichier
 * \param action Action avec ses paramètres (inutilisé ici)
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