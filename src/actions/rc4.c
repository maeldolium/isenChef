#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/actions.h"

/**
 * \brief Permet d'échanger deux caractères en mémoire
 *
 * La fonction swap échange deux caractère chara et charb en mémoire
 * en passant par une variable temporaire tmp.
 *
 * \param chara Pointeur vers un caractère a à échanger
 * \param charb Pointeur vers un caractère b à échanger
 * \return Aucun retour
 */
void swap(unsigned char *chara, unsigned char *charb)
{
    unsigned char tmp = *chara;
    *chara = *charb;
    *charb = tmp;
}

/**
 * \brief Permets de chiffrer ou déchiffrer un
 * buffer à l'aide de l'algorithme RC4.
 *
 * La fonction rc4 applique l'algorithme de chiffrement
 * symétrique RC4 sur un buffer d'entrée. Elle génère un tableau de
 * clés pseudo-aléatoires et les combines aux données par une
 * opération XOR.
 *
 * La même fonction permet à la fois de chiffrer et de déchiffrer
 * les données, à condition d'utiliser la même clé.
 *
 * L'algorithme est composé des étapes:
 * -KSA (Key Scheduling Algorithm) : initialisation et mélange du
 * tableau S en fonction de la clé fournie par l'utilisateur.
 * -PRGA (Pseudo-Random Generation Algorithm) : génération d'un octet
 * pseudo-aléatoire pour chaque octet du buffer et combiné par XOR.
 *
 * \param input_buffer Pointeur vers le buffer d'entrée contenant les
 * données à chiffrer ou déchiffrer
 * \param action Pointeur vers la structure Action contenant
 * la clé utilisé pour le chiffrement RC4
 * \return Retourne un buffer contenant les données chiffrées ou
 * déchiffrées. En cas d'erreur, retourne un buffer vide.
 */
FileBuffer rc4(const FileBuffer *input_buffer, const Action *action)
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

    // KSA (Key Scheduling Algorithm) - Initialisation du tableau S
    unsigned char S[256];
    for (size_t i = 0; i < 256; i++)
    {
        S[i] = i;
    }

    // Mélange du tableau S avec la clé (KSA)
    size_t j = 0;
    size_t key_length = strlen(action->key);
    for (size_t i = 0; i < 256; i++)
    {
        j = (j + S[i] + action->key[i % key_length]) % 256;
        swap(&S[i], &S[j]);
    }

    // Allocation mémoire pour les données chiffrées
    temp.size = input_buffer->size;
    temp.data = malloc(temp.size + 1);

    // PRGA (Pseudo-Random Generation Algorithm) - Chiffrement des données
    size_t i = 0;
    j = 0;
    for (size_t byte = 0; byte < input_buffer->size; byte++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(&S[i], &S[j]);
        unsigned char octet = S[(S[i] + S[j]) % 256];       // Génère un octet pseudo-aléatoirement
        temp.data[byte] = input_buffer->data[byte] ^ octet; // XOR avec l'octet généré
    }

    // temp.data[temp.size] = '\0';

    return temp;
}