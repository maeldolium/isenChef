#include <stdio.h>
#include <stdlib.h>

#include "../../includes/actions.h"

FileBuffer reverse(const FileBuffer *input_buffer, const Action *action)
{
    // Initialisation du buffer
    FileBuffer temp;
    temp.data = NULL;
    temp.size = 0;

    // Vérifier les paramètres requis
    if (!input_buffer || !input_buffer->data || input_buffer->size == 0)
    {
        return temp;
    }

    temp.size = input_buffer->size;
    temp.data = malloc(temp.size);
    if (!temp.data)
    {
        temp.size = 0;
        return temp;
    }

    for (size_t i = 0; i < input_buffer->size; i++)
    {
        temp.data[i] = input_buffer->data[input_buffer->size - 1 - i];
    }

    return temp;
}