#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/errors.h"
#include "../includes/format_dispatcher.h"
#include "formats.h"

// Tableau de structure des formats connus
static FormatEntry formats[] = {{"bytes", NULL, NULL}, // Pas d'encodage/décodage nécessaire
                                {"hex", to_hex, from_hex},
                                {"base64", to_base64, from_base64}};

/**
 * \brief Vérifie si un format donné est valide
 *
 * La fonction is_valid_format vérifie si le nom du format passé en paramètre
 * existe dans la liste des formats disponibles.
 *
 * \param format_name Pointeur vers le nom du format à vérifier
 * \return Retourne 1 si le format est valide, 0 sinon
 */
int is_valid_format(const char *format_name)
{
    if (!format_name)
        return 0;

    int formatsCount = sizeof(formats) / sizeof(formats[0]);

    for (int i = 0; i < formatsCount; i++)
    {
        if (strcmp(format_name, formats[i].name) == 0)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * \brief Permet de décoder le fichier d'entrée pour le traiter
 * en bytes dans le reste du programme.
 *
 * La fonction dispatch_format_decode prend un buffer d'entrée input_buffer et
 * un Argument args. Elle vérifie que le nom du format d'entrée est connu, si
 * oui, elle applique le décodage associé afin de traiter les données en bytes
 * dans le reste du programme, sinon elle retourne une erreur.
 *
 * \param input_buffer Pointeur vers le buffer d'entrée contenant les données du
 * fichier
 * \param args Pointeur vers la structure Argument qui contient le format du
 * fichier d'entrée
 * \return Retourne la structure FileBuffer contenant les données du fichier en
 * bytes, retourne une structure vide en cas d'erreur.
 */
FileBuffer dispatch_format_decode(const FileBuffer *input_buffer, const Arguments *args)
{
    FileBuffer disformat;
    disformat.data = NULL;
    disformat.size = 0;

    // Vérification des paramètres requis
    if (!input_buffer || !input_buffer->data || input_buffer->size == 0)
    {
        return disformat;
    }

    int formatsCount = sizeof(formats) / sizeof(formats[0]);

    int found = 0;
    // Recherche le nom du format dans le tableau
    for (size_t i = 0; i < formatsCount; i++)
    {
        if (strcmp(args->input_format, formats[i].name) == 0)
        {
            // Applique le décodage s'il existe
            if (formats[i].decode)
            {
                disformat = formats[i].decode(input_buffer);
            }
            // Sinon copie le buffer à l'identique
            else
            {
                disformat = *input_buffer;
            }

            found = 1;
            break;
        }
    }

    // Retourne une erreur si décodage non trouvé
    if (found == 0)
    {
        print_error(ERR_UNKNOWN_FORMAT, args->input_format);
        return disformat;
    }

    return disformat;
}

/**
 * \brief Permet d'encoder le fichier de sortie au format demandé par
 * l'utilisateur.
 *
 * La fonction dispatch_format_encode prend un buffer d'entrée input_buffer et
 * un Argument args. Elle vérifie que le nom du format de sortie est connu, si
 * oui, elle applique l'encodage associé sinon elle retourne une erreur.
 *
 * \param input_buffer Pointeur vers le buffer d'entrée contenant les données du
 * fichier
 * \param args Pointeur vers la structure Argument qui contient le format du
 * fichier de sortie
 * \return Retourne la structure FileBuffer contenant les données du fichier
 * encodées, retourne une structure vide en cas d'erreur.
 */
FileBuffer dispatch_format_encode(const FileBuffer *input_buffer, const Arguments *args)
{
    FileBuffer disformat;
    disformat.data = NULL;
    disformat.size = 0;

    // Vérification des paramètres requis
    if (!input_buffer || !input_buffer->data || input_buffer->size == 0)
    {
        return disformat;
    }

    int formatsCount = sizeof(formats) / sizeof(formats[0]);

    int found = 0;
    // Recherche le nom du format dans le tableau
    for (size_t i = 0; i < formatsCount; i++)
    {
        if (strcmp(args->output_format, formats[i].name) == 0)
        {
            // Applique l'encodage s'il existe
            if (formats[i].encode)
            {
                disformat = formats[i].encode(input_buffer);
            }
            // Sinon copie le buffer à l'identique
            else
            {
                disformat = *input_buffer;
            }

            found = 1;
            break;
        }
    }

    // Envoie une erreur si format non trouvé
    if (found == 0)
    {
        print_error(ERR_UNKNOWN_FORMAT, args->output_format);
        return disformat;
    }

    return disformat;
}