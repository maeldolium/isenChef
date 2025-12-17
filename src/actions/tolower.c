#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../includes/actions.h"
#include "../../includes/file.h"

/**
 *
 * \brief Permet de passer le contenu d'un buffer en minuscule.
 *
 * La fonction to_lowercase crée un buffer temporaire temp, lui donne
 * la taille du buffer d'entrée puis transforme les caractères du
 * buffer d'entrée et les copies dans le buffer temporaire.
 *
 * \param input_buffer Buffer d'entrée contenant les données
 * du fichier
 * \return Retourne un buffer temporaire, retourne le buffer vide
 * en cas d'erreur
 */
FileBuffer to_lowercase(const FileBuffer *input_buffer)
{
    FileBuffer temp;
    temp.data = NULL;
    temp.size = 0;

    if (!input_buffer || !input_buffer->data || input_buffer->size == 0)
    {
        return temp;
    }

    temp.size = input_buffer->size;
    temp.data = malloc(temp.size + 1);
    if (!temp.data)
    {
        temp.size = 0;
        return temp;
    }

    for (size_t i = 0; i < input_buffer->size; i++)
    {
        temp.data[i] = tolower(input_buffer->data[i]);
    }

    temp.data[temp.size] = '\0';

    return temp;
}