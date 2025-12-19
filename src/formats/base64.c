#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/actions.h"

// Tableau content l'alphabet base64
const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * \brief Convertit un caractère base64 en sa valeur numérique
 *
 * La fonction base64_char_to_value prend un caractère base64 (A-Z, a-z, 0-9, +, /)
 * et le convertit en sa valeur numérique correspondante (0-63). Le caractère
 * est modifié directement dans la variable.
 *
 * \param c Pointeur vers le caractère base64 à convertir. Après l'appel,
 * contient la valeur numérique (0-63)
 *
 * \note Les valeurs correspondent à la position dans l'alphabet base64 :
 * - A-Z : 0-25
 * - a-z : 26-51
 * - 0-9 : 52-61
 * - +/  : 62-63
 */
void base64_char_to_value(unsigned char *c)
{
    if (*c >= 'A' && *c <= 'Z')
    {
        *c = *c - 'A';
    }
    else if (*c >= 'a' && *c <= 'z')
    {
        *c = *c - 'a' + 26;
    }
    else if (*c >= '0' && *c <= '9')
    {
        *c = *c - '0' + 52;
    }
    else
    {
        *c = *c - '+' + 62;
    }
}

/**
 * \brief Permet de convertir le buffer en base64
 *
 * La fonction to_base64 prend un buffer d'entrée input_buffer et le convertit
 * en base64. Elle encode les données avec l'alphabet base64 standard.
 *
 * \param input_buffer Pointeur vers le buffer d'entrée contenant les données du fichier
 * \return Retourne un buffer avec les données transformées, retourne
 * un buffer vide en cas d'erreur
 */
FileBuffer to_base64(const FileBuffer *input_buffer)
{
    // Initialisation du buffer
    FileBuffer temp;
    temp.data = NULL;
    temp.size = 0;

    // Vérification des paramètres requis
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

/**
 * \brief Permet de convertir un buffer d'entrée en base64 en bytes.
 *
 * La fonction from_base64 prend un buffer d'entrée input_buffer en base64 et le convertit
 * en bytes. Elle décode les données à partir de l'alphabet base64 standard.
 *
 * \param input_buffer Pointeur vers le buffer d'entrée contenant les données du fichier
 * \return Retourne un buffer avec les données transformées, retourne
 * un buffer vide en cas d'erreur
 *
 * \note Amélioration possible :
 * - Interdire un caractère '=' au milieu des données -> '=' représente le padding
 * et ne peut se trouver qu'en avant-dernière ou dernière position
 */
FileBuffer from_base64(const FileBuffer *input_buffer)
{
    // Initialisation du buffer
    FileBuffer temp;
    temp.data = NULL;
    temp.size = 0;

    // Vérification des paramètres requis
    if (!input_buffer || !input_buffer->data || input_buffer->size == 0)
    {
        return temp;
    }

    // Vérifier que le buffer d'entrée est valide
    if (input_buffer->size % 4 != 0)
    {
        return temp;
    }

    // Validation des caractères sinon erreur
    for (size_t i = 0; i < input_buffer->size; i++)
    {
        int found = 0;
        // Si le caractère fait parti de l'alphabet base64
        for (size_t j = 0; j < strlen(base64_table); j++)
        {
            if (input_buffer->data[i] == base64_table[j] || input_buffer->data[i] == '=')
            {
                found = 1;
                break;
            }
        }

        // Sinon on retourne un buffer vide
        if (found == 0)
        {
            return temp;
        }
    }

    // Calcul de la taille de la sortie
    if (input_buffer->data[input_buffer->size - 1] == '=')
    {
        temp.size = ((input_buffer->size / 4) * 3) - 1; // padding = -> 1 bytes
    }
    else if (input_buffer->data[input_buffer->size - 2] == '=')
    {
        temp.size = ((input_buffer->size / 4) * 3) - 2; // padding == -> 2 byte
    }
    else
    {
        temp.size = (input_buffer->size / 4) * 3; // pas de padding -> 3 bytes
    }

    // Allocation de la mémoire
    temp.data = malloc(temp.size + 1);

    // Transformation des caractères base64 en bytes
    size_t out_index = 0;
    for (size_t i = 0; i < input_buffer->size; i += 4)
    {
        unsigned char c0 = input_buffer->data[i];
        unsigned char c1 = input_buffer->data[i + 1];
        unsigned char c2 = input_buffer->data[i + 2];
        unsigned char c3 = input_buffer->data[i + 3];

        base64_char_to_value(&c0);
        base64_char_to_value(&c1);
        if (c2 != '=')
        {
            base64_char_to_value(&c2);
        }
        if (c3 != '=')
        {

            base64_char_to_value(&c3);
        }

        if (c2 == '=')
        {
            unsigned char b0 = (c0 << 2) | (c1 >> 4);

            temp.data[out_index++] = b0;
        }
        else if (c3 == '=')
        {
            unsigned char b0 = (c0 << 2) | (c1 >> 4);
            unsigned char b1 = (c1 << 4) | (c2 >> 2);

            temp.data[out_index++] = b0;
            temp.data[out_index++] = b1;
        }
        else
        {
            unsigned char b0 = (c0 << 2) | (c1 >> 4);
            unsigned char b1 = (c1 << 4) | (c2 >> 2);
            unsigned char b2 = (c2 << 6) | c3;

            temp.data[out_index++] = b0;
            temp.data[out_index++] = b1;
            temp.data[out_index++] = b2;
        }
    }

    temp.data[temp.size] = '\0';

    return temp;
}