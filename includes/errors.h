#ifndef ERRORS_H
#define ERRORS_H

typedef enum
{
    ERR_OK = 0, // Pas d'erreur

    // Fichier
    ERR_FILE_NOT_FOUND,
    ERR_FILE_READ,
    ERR_FILE_WRITE,

    // Arguments
    ERR_MISSING_ARGUMENT,
    ERR_INVALID_ARGUMENT,
    ERR_UNKNOWN_ACTION,
    ERR_UNKNOWN_FORMAT,

    // Format
    ERR_INVALID_HEX,
    ERR_INVALID_BASE64,

    // Actions
    ERR_MISSING_KEY,
    ERR_INVALID_KEY,

    // Mémoire
    ERR_MEMORY_ALLOCATION,

} ErrorCode;

void print_error(ErrorCode code, const char *context);

#endif