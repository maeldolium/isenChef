#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/actions.h"

/**
 *
 * \brief Permet de convertir le buffer en base64
 *
 * La fonction to_base64 prend un buffer d'entrée input_buffer, puis crée
 * et initialise un buffer temporaire temp. Ensuite elle donne à temp
 *
 * \param input_buffer Buffer d'entrée contenant les données du fichier
 * \param action Action avec ses paramètres (inutilisé ici)
 * \return Retourne un buffer avec les données transformées, retourne
 * un buffer vide en cas d'erreur
 */
FileBuffer to_base64(const FileBuffer *input_buffer, const Action *action)
{
    FileBuffer temp;
    temp.data = NULL;
    temp.size = 0;

    if (!input_buffer || !input_buffer->data || input_buffer->size == 0)
    {
        return temp;
    }

    // Base64 encode 3 bytes en 4 caractères, arrondi à la hausse avec +2
    temp.size = 4 * ((input_buffer->size + 2) / 3);
    temp.data = malloc(temp.size + 1);
    if (!temp.data)
    {
        temp.size = 0;
        return temp;
    }

    // Table de base64
    const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    size_t in_index = 0;
    size_t out_index = 0;

    // Traiter les groupes de 3 bytes (24 bits) et les convertir en 4 caractères base64 (4*6=24 bits)
    while (in_index + 2 < input_buffer->size)
    {

        unsigned char b0 = input_buffer->data[in_index];
        unsigned char b1 = input_buffer->data[in_index + 1];
        unsigned char b2 = input_buffer->data[in_index + 2];

        // b0: extraire les 6 bits supérieurs (bits 7-2)
        temp.data[out_index++] = base64_table[(b0 & 0xFC) >> 2];

        // Combiner les 2 bits inférieurs de b0 + 4 bits supérieurs de b1
        temp.data[out_index++] = base64_table[(b0 & 0x3) << 4 | (b1 & 0xF0) >> 4];

        // Combiner les 4 bits inférieurs de b1 + 2 bits supérieurs de b2
        temp.data[out_index++] = base64_table[(b1 & 0xF) << 2 | (b2 & 0xC0) >> 6];

        // b2: extraire les 6 bits inférieurs (bits 5-0)
        temp.data[out_index++] = base64_table[(b2 & 0x3F)];
        in_index += 3;
    }

    // Traiter les bytes restants(moins de 3 bytes à la fin) int remaining = input_buffer -> size - in_index;
    int remaining = input_buffer->size - in_index;

    // Cas où 1 byte reste: ajouter 2 caractères + "=="
    if (remaining == 1)
    {
        unsigned char b0 = input_buffer->data[in_index];

        temp.data[out_index++] = base64_table[(b0 & 0xFC) >> 2];
        temp.data[out_index++] = base64_table[(b0 & 0x03) << 4];
        temp.data[out_index++] = '=';
        temp.data[out_index++] = '=';
    }
    // Cas où 2 bytes restent: ajouter 3 caractères + "="
    else if (remaining == 2)
    {
        unsigned char b0 = input_buffer->data[in_index];
        unsigned char b1 = input_buffer->data[in_index + 1];

        temp.data[out_index++] = base64_table[(b0 & 0xFC) >> 2];
        temp.data[out_index++] = base64_table[((b0 & 0x03) << 4) | ((b1 & 0xF0) >> 4)];
        temp.data[out_index++] = base64_table[(b1 & 0x0F) << 2];
        temp.data[out_index++] = '=';
    }

    // Ajouter \0 à la fin
    temp.data[out_index] = '\0';

    return temp;
}