#include <stdio.h>

#include "../includes/errors.h"

void print_error(ErrorCode code, const char *context)
{
    switch (code)
    {
    // Erreurs fichier
    case ERR_FILE_NOT_FOUND:
        if (context)
        {
            printf("Erreur : fichier introuvable : %s\nError: file not found: %s\n", context,
                   context);
        }
        else
        {
            printf("Erreur : fichier introuvable.\nError: file not found.\n");
        }
        break;
    case ERR_FILE_READ:
        if (context)
        {
            printf("Erreur: erreur lors de la lecture du fichier : %s\nError: error "
                   "occurred during file reading: %s\n",
                   context, context);
        }
        else
        {
            printf("Erreur: erreur lors de la lecture du fichier.\nError: error "
                   "occurred during file reading.\n");
        }
        break;
    case ERR_FILE_WRITE:
        if (context)
        {
            printf("Erreur: erreur lors de l'écriture du fichier : %s\nError: error "
                   "occurred during file writing: %s\n",
                   context, context);
        }
        else
        {
            printf("Erreur: erreur lors de l'écriture du fichier.\nError: error "
                   "occurred during file writing.\n");
        }
        break;

    // Erreurs arguments
    case ERR_INVALID_ARGUMENT:
        if (context)
        {
            printf("Erreur: argument invalide : %s\nError: invalid argument: %s\n", context,
                   context);
        }
        else
        {
            printf("Erreur: argument invalide.\nError: invalid argument.\n");
        }
        break;
    case ERR_MISSING_ARGUMENT:
        if (context)
        {
            printf("Erreur: argument manquant : %s\nError: missing argument: %s\n", context,
                   context);
        }
        else
        {
            printf("Erreur: argument manquant?\nError: missing argument.\n");
        }
        break;
    case ERR_UNKNOWN_ACTION:
        if (context)
        {
            printf("Erreur: action inconnue : %s\nError: unknown action: %s\n", context, context);
        }
        else
        {
            printf("Erreur: action inconnue.\nError: unknown action.\n");
        }
        break;
    case ERR_UNKNOWN_FORMAT:
        if (context)
        {
            printf("Erreur: format inconnu : %s\nError: unknown format: %s\n", context, context);
        }
        else
        {
            printf("Erreur: format inconnu.\nError: unknown format.\n");
        }
        break;

    // Erreurs format
    case ERR_INVALID_BASE64:
        if (context)
        {
            printf("Erreur: format base64 invalide : %s\nError: invalid base64 "
                   "format: %s\n",
                   context, context);
        }
        else
        {
            printf("Erreur: format base64 invalide.\nError: invalid base64 format.\n");
        }
        break;
    case ERR_INVALID_HEX:
        if (context)
        {
            printf("Erreur: format hex invalide : %s\nError: invalid hex format: %s\n", context,
                   context);
        }
        else
        {
            printf("Erreur: format hex invalide.\nError: invalid hex format.\n");
        }
        break;

    // Erreurs actions
    case ERR_MISSING_KEY:
        if (context)
        {
            printf("Erreur: clé manquante pour l'action : %s\nError: missing key for "
                   "action : %s\n",
                   context, context);
        }
        else
        {
            printf("Erreur: clé manquante.\nError: missing key.\n");
        }
        break;
    case ERR_INVALID_KEY:
        if (context)
        {
            printf("Erreur: clé invalide : %s\nError: invalid key: %s\n", context, context);
        }
        else
        {
            printf("Erreur: clé invalide.\nError: invalid key.\n");
        }
        break;

    // Erreur mémoire:
    case ERR_MEMORY_ALLOCATION:
        printf("Erreur: erreur lors de l'allocation de la mémoire.\nError: memory "
               "allocation error.\n");
        break;
    default:
        if (context)
        {
            printf("Erreur inconnue : %s\nError: unknown error: %s\n", context, context);
        }
        else
        {
            printf("Erreur inconnue.\nError: unknown error.\n");
        }
        break;
    }
}
