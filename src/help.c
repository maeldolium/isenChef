#include <stdio.h>

#include "../includes/help.h"

void print_help(void)
{
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║          isenChef - Outil de transformation de fichiers        ║\n");
    printf("║                    inspiré par CyberChef                       ║\n");
    printf("║                    Auteur : Maël                               ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n");

    printf("UTILISATION :\n");
    printf("─────────────\n");
    printf("  ./isenChef.exe [OPTIONS]\n");
    printf("\n");
    printf("SYNTAXE GÉNÉRALE :\n");
    printf("──────────────────\n");
    printf("  ./isenChef.exe --in <fichier_entrée> --input-format <format> \\\n");
    printf("           [--action <action> [--key <clé>]] \\\n");
    printf("           --out <fichier_sortie> --output-format <format>\n");
    printf("\n");

    printf("OPTIONS DISPONIBLES :\n");
    printf("─────────────────────\n");
    printf("  --in <fichier>           Chemin du fichier d'entrée\n");
    printf("\n");
    printf("  --out <fichier>          Chemin du fichier de sortie\n");
    printf("\n");
    printf("  --input-format <fmt>     Format d'entrée (voir formats ci-dessous)\n");
    printf("\n");
    printf("  --output-format <fmt>    Format de sortie (voir formats ci-dessous)\n");
    printf("\n");
    printf("  --action <action>        Action à appliquer (optionnel)\n");
    printf("\n");
    printf("  --key <clé>              Clé pour les actions qui en nécessitent une\n");
    printf("                           (dépend de l'action)\n");
    printf("\n");
    printf("  --help                   Affiche ce message d'aide\n");
    printf("\n");

    printf("FORMATS SUPPORTÉS :\n");
    printf("───────────────────\n");
    printf("  bytes      Octets bruts (par défaut)\n");
    printf("  hex        Codage hexadécimal\n");
    printf("  base64     Codage Base64\n");
    printf("\n");
    printf("  Note importante :\n");
    printf("    - Les formats d'entrée sont décodés en octets avant l'action\n");
    printf("    - Les formats de sortie sont encodés après l'action\n");
    printf("\n");

    printf("ACTIONS SUPPORTÉES :\n");
    printf("────────────────────\n");
    printf("  Sans clé :\n");
    printf("    uppercase   Convertir le texte en majuscules\n");
    printf("    lowercase   Convertir le texte en minuscules\n");
    printf("    reverse     Inverser le contenu du fichier\n");
    printf("\n");
    printf("  Avec clé :\n");
    printf("    caesar      Chiffre de César\n");
    printf("    XOR         Chiffrement XOR\n");
    printf("    RC4         Chiffrement RC4)\n");
    printf("\n");

    printf("GESTION DES CLÉS :\n");
    printf("──────────────────\n");
    printf("  - Les clés numériques sont supportées pour caesar et xor\n");
    printf("  - Les clés numériques signées sont permises pour caesar\n");
    printf("    (valeur négative = déchiffrement)\n");
    printf("  - Les clés texte sont supportées pour xor et rc4\n");
    printf("\n");

    printf("CHEMINS DE FICHIERS :\n");
    printf("─────────────────────\n");
    printf("  - Les chemins sont relatifs au répertoire de build (builddir/)\n");
    printf("  - Pour accéder à un fichier à la racine du projet : utiliser ../\n");
    printf("  - Exemples de chemins :\n");
    printf("    - Fichier dans builddir/ : mon_fichier.txt\n");
    printf("    - Fichier à la racine : ../mon_fichier.txt\n");
    printf("    - Fichier dans un sous-dossier : ../dossier/mon_fichier.txt\n");
    printf("\n");

    printf("GESTION DES ERREURS :\n");
    printf("─────────────────────\n");
    printf("  - Les arguments invalides sont signalés avec des messages explicites\n");
    printf("  - Les fichiers manquants et les actions inconnues sont détectés\n");
    printf("  - Les encodages invalides (hex/base64) sont rejetés\n");
    printf("\n");

    printf("POUR PLUS D'INFORMATIONS :\n");
    printf("──────────────────────────\n");
    printf("  Consultez le fichier README.md pour la documentation détaillée\n");
    printf("\n");
}