#include <stdio.h>
#include <stdlib.h>

#include "../../includes/actions.h"

/**
 * \brief Convertit un caractère hexadécimal en sa valeur numérique
 *
 * La fonction hex_char_to_value prend un caractère hexadécimal (0-9, a-f, A-F)
 * et le convertit en sa valeur numérique correspondante (0-15). Le caractère
 * est modifié directement dans la variable.
 *
 * \param c Pointeur vers le caractère hexadécimal à convertir. Après l'appel,
 * contient la valeur numérique (0-15)
 *
 * \note Les caractères majuscules (A-F) et minuscules (a-f) sont acceptés
 */
void hex_char_to_value(unsigned char *c)
{
    if (*c >= '0' && *c <= '9')
    {
        *c = *c - '0';
    }
    else if (*c >= 'a' && *c <= 'f')
    {
        *c = *c - 'a' + 10;
    }
    else
    {
        *c = *c - 'A' + 10;
    }
}

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
FileBuffer to_hex(const FileBuffer *input_buffer)
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

    // Allocation de la mémoire
    temp.size = input_buffer->size * 2;
    temp.data = malloc(temp.size + 1);
    if (!temp.data)
    {
        temp.size = 0;
        return temp;
    }

    // Transforamtion des bytes en caractères hexadécimaux
    for (size_t i = 0; i < input_buffer->size; i++)
    {
        sprintf((char *)&temp.data[i * 2], "%02X", (unsigned char)input_buffer->data[i]);
    }

    temp.data[temp.size] = '\0';

    return temp;
}

/**
 * \brief Permet de transformer des caractères héxadécimaux en bytes.
 *
 * La fonction from_hex prend un buffer d'entrée contenant des caractères hexadécimaux
 * et le transforme en bytes. Chaque paire de 2 caractères hexadécimaux
 * est convertie en 1 byte.
 *
 * \param input_buffer Pointeur vers le buffer d'entrée contenant les données hexadécimales
 * \return Retourne un buffer avec les données transformées, retourne
 * un buffer vide en cas d'erreur
 */
FileBuffer from_hex(const FileBuffer *input_buffer)
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
    if ((input_buffer->size % 2) != 0)
    {
        return temp;
    }

    // Vérification de la validité des caractères du buffer d'entrée
    for (size_t i = 0; i < input_buffer->size; i++)
    {
        if (!(input_buffer->data[i] >= '0' && input_buffer->data[i] <= '9') && !(input_buffer->data[i] >= 'a' && input_buffer->data[i] <= 'f') && !(input_buffer->data[i] >= 'A' && input_buffer->data[i] <= 'F'))
        {
            return temp;
        }
    }

    // Allocation de la mémoire
    temp.size = input_buffer->size / 2;
    temp.data = malloc(temp.size + 1);
    if (!temp.data)
    {
        temp.size = 0;
        return temp;
    }

    // Transformation des caractères hexadécimaux en bytes
    for (size_t i = 0; i < input_buffer->size; i += 2)
    {
        unsigned char c1 = input_buffer->data[i];
        unsigned char c2 = input_buffer->data[i + 1];

        hex_char_to_value(&c1);
        hex_char_to_value(&c2);

        unsigned char byte = (c1 << 4) | c2;

        temp.data[i / 2] = byte;
    }

    temp.data[temp.size] = '\0';

    return temp;
}
