#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "../includes/file.h"

/**
 * \brief Lit le fichier donner par l'utilisateur et le stocke dans un buffer
 *
 * La fonction read_file crée un buffer, puis, ouvre en binaire le fichier donné par
 * l'utilisateur et stocke sa taille ainsi que ses données dans le buffer.
 *
 * \param FileBuffer Structure du buffer définie dans file.h, elle contient la taille
 * du buffer ainsi que ses données.
 * \param path Chemin vers le fichier d'entrée donné par l'utilisateur.
 * \return Retourne le buffer contenant les informations du fichiers. S'il y a
 * une erreur dans l'ouverture, l'allocation de la mémoire ou la lecture du fichier,
 * ferme le fichier et retourne un buffer incomplet et libère la mémoire.
 */
FileBuffer read_file(const char *path)
{
    FileBuffer buf;
    buf.data = NULL;
    buf.size = 0;

    FILE *f_in = fopen(path, "rb");
    if (f_in == NULL)
    {
        return buf;
    }

    fseek(f_in, 0, SEEK_END);
    buf.size = ftell(f_in);
    rewind(f_in);

    buf.data = malloc(buf.size);
    if (buf.data == NULL)
    {
        fclose(f_in);
        return buf;
    }

    size_t n = fread(buf.data, 1, buf.size, f_in);
    if (n != buf.size)
    {
        free_file_buffer(&buf);
        fclose(f_in);
        return buf;
    }

    fclose(f_in);

    return buf;
}

/**
 *
 * \brief Permet l'écriture de données dans un fichier dont le chemin est indiqué
 * par l'utilisateur.
 *
 * La fonction write_file vérifie si toutes les informations nécessaires sont présentes
 * (sinon retourne -1), puis ouvre le fichier de sortie et écrit les données dedans en
 * binaire.
 *
 * \param path Chemin du fichier de sortie donné par l'utilisateur.
 * \param buf Buffer contenant les données du fichier d'entrée.
 * \return Retourne la valeur 0 si tout s'est bien passé, -1 en cas d'erreur.
 */
int write_file(const char *path, const FileBuffer *buf)
{
    if (path == NULL || buf == NULL || buf->data == NULL)
    {
        return -1;
    }

    FILE *f_out = fopen(path, "wb");
    if (f_out == NULL)
    {
        return -1;
    }

    size_t n = fwrite(buf->data, 1, buf->size, f_out);
    if (n != buf->size)
    {
        fclose(f_out);
        return -1;
    }

    fclose(f_out);
    return 0;
}

/**
 *
 * \brief Permet de libérer la mémoire allouer au buffer et de le réinitialiser.
 *
 * \param buf Buffer contenant les données des fichiers.
 */
void free_file_buffer(FileBuffer *buf)
{
    free(buf->data);
    buf->data = NULL;
    buf->size = 0;
}
