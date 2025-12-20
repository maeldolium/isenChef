#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/actions.h"

/**
 * \brief Permet de vérifier si une clé est entièrement composée de chiffres
 *
 * La fonction is_numeric_key parcourt la chaîne de caractères passée en paramètre
 * et vérifie que chaque caractère est un chiffre (de '0' à '9').
 *
 * \param key Pointeur vers la chaîne de caractères contenant la clé à vérifier
 * \return Retourne 1 si la clé est numérique, 0 sinon ou si la clé est NULL/vide
 */
int is_numeric_key(const char *key)
{
    // Erreur si la clé est nulle
    if (!key || *key == '\0')
    {
        return 0;
    }

    // Vérifie que chaque caractère de la clé est numérique
    for (size_t i = 0; key[i]; i++)
    {
        if (key[i] < '0' || key[i] > '9')
        {
            return 0;
        }
    }

    return 1;
}

/**
 * \brief Permet de chiffre ou déchiffre un buffer à l'aide de XOR
 *
 * La fonction xor applique un chiffrement avec XOR à un buffer d'entrée.
 * Avant d'appliquer le chiffrement, elle vérifie si la clé est composée
 * uniquement de chiffre ou si elle contient du texte afin de choisir entre
 * un XOR mono-octet ou un XOR multi-octet.
 *
 * \param input_buffer Pointeur vers le buffer d'entrée contenant les données
 * du fichier à chiffrer ou déchiffrer
 * \param action Pointeur vers la structure Action contenant la clé à utiliser
 * pour le chiffremenet/déchiffrement
 * \return Retourne un buffer contenant les données chiffrées/déchiffrées. En
 * cas d'erreur, retourne un buffer vide.
 */
FileBuffer xor(const FileBuffer *input_buffer, const Action *action)
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

    if (!action || !action->key || strlen(action->key) == 0)
    {
        return temp;
    }

    // Allocation de la mémoire
    temp.size = input_buffer->size;
    temp.data = malloc(temp.size + 1);
    if (!temp.data)
    {
        temp.size = 0;
        return temp;
    }

    // Chiffrage des données avec XOR
    // Si la clé est numérique : XOR mono-octet
    if (is_numeric_key(action->key))
    {
        unsigned char key = (unsigned char)atoi(action->key);

        for (size_t i = 0; i < input_buffer->size; i++)
        {
            temp.data[i] = input_buffer->data[i] ^ key;
        }
    }
    // Sinon XOR multi-octet, la clé est considéré comme un flux répété
    else
    {
        size_t key_length = strlen(action->key);

        for (size_t i = 0; i < input_buffer->size; i++)
        {
            temp.data[i] = input_buffer->data[i] ^ (unsigned char)action->key[i % key_length];
        }
    }

    temp.data[temp.size] = '\0';

    return temp;
}