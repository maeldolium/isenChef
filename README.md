# IsenChef

IsenChef est un projet réalisé en C dans le cadre de ma 3ème année d'école d'ingénieur.

Ce projet prend comme référence [CyberChef](https://gchq.github.io/CyberChef/).

---

## Sommaire
- [Prérequis](#prérequis)
- [Technologies](#technologies)
- [Fonctionnalités](#fonctionnalités)
- [Compiler](#compiler)
- [Utilisation](#utilisation)
- [Structure](#structure)

---

## Prérequis

Avant de compiler le projet, assurez-vous d'avoir les éléments suivants installés :

- **Meson** : Système de build (v0.57 ou plus récent)
- **Ninja** : Backend de compilation pour Meson

---

## Technologies

- Langage: C
- Système de build: Meson & Ninja
- Outil de formatage : clang-format (LLVM)
- Outil : Valgrind (Détection fuites de mémoire)

---

## Fonctionnalités

- Transformation majuscule
- Transformation minuscule
- Inversion des données
- Encodage hexadécimal
- Encodage base64
- Encodage bytes
- Chiffrement César
- Chiffrement RC4
- Chiffrement XOR
- Lecture d'un fichier
- Ecriture sur le disque
- Affichage des erreurs
- Affichage des aides

---

## Compiler

### Première compilation

Pour configurer le projet avec Meson et générer les fichiers de compilation Ninja, exécutez :

```bash
meson setup builddir
```

Cette commande crée le dossier `builddir` et configure le projet en générant les fichiers de build.

### Compilations suivantes

Une fois le `builddir` créé, il n'est plus nécessaire de réexécuter `meson setup`. Vous pouvez compiler directement avec Ninja :

1. Accédez au dossier `builddir` :

```bash
cd builddir
```

2. Lancez Ninja pour compiler le projet :

```bash
ninja
```

Cela générera l'exécutable du projet `isenChef.exe` dans le répertoire `builddir`.

## Utilisation

### Affichage de l'aide

Pour afficher la liste complète des commandes disponibles et leur utilisation :

```bash
./isenChef --help
```

### Utilisation générale

La syntaxe générale du programme est :

```bash
./isenChef --in <fichier_entrée> --action <nom_action> [--key <clé>] --out <fichier_sortie>
```

### Paramètres

- `--in <fichier>` : Fichier d'entrée à traiter
- `--action <action>` : Action à effectuer (par ex. : `caesar`, `RC4`, `XOR`, `hex`, `base64`, `uppercase`, `lowercase`, `reverse`)
- `--key <clé>` : Clé de chiffrement (obligatoire pour certaines actions comme `caesar` et `RC4`)
- `--out <fichier>` : Fichier de sortie où écrire le résultat

**Important** : Il est nécessaire de fournir le chemin complet ou relatif vers les fichiers. Puisque l'exécutable `isenChef` se trouve dans le dossier `builddir`, utilisez les chemins relatifs en conséquence. Par exemple, si votre fichier d'entrée se trouve à la racine du projet, utilisez `../input.txt`.

### Exemples

Transformer un texte en majuscules (fichier à la racine du projet) :

```bash
./isenChef --in ../input.txt --action toupper --out ../output.txt
```

Chiffrer avec César (fichiers dans le dossier builddir) :

```bash
./isenChef --in ./input.txt --action caesar --key 3 --out ./output.txt
```

Chiffrer avec RC4 (chemin complet) :

```bash
./isenChef --in "C:\chemin\complet\input.txt" --action rc4 --key "maclé" --out "C:\chemin\complet\output.txt"
```

---

## Structure

```
isenChef/
├── src/                          # Code source principal
│   ├── main.c                    # Point d'entrée du programme
│   ├── args.c                    # Gestion des arguments de ligne de commande
│   ├── args_handlers.c           # Traitements spécifiques des arguments
│   ├── file.c                    # Gestion des fichiers (lecture/écriture)
│   ├── action_dispatcher.c       # Dispatcher pour les différentes actions
│   ├── format_dispatcher.c       # Dispatcher pour les différents formats
│   ├── errors.c                  # Gestion et affichage des erreurs
│   ├── help.c                    # Affichage de l'aide du programme
│   ├── actions/                  # Dossier contenant toutes les actions
│   │   ├── caesar.c              # Chiffrement César
│   │   ├── rc4.c                 # Chiffrement RC4
│   │   ├── xor.c                 # Chiffrement XOR
│   │   ├── reverse.c             # Inversion de contenu
│   │   ├── toupper.c             # Transformation en majuscules
│   │   └── tolower.c             # Transformation en minuscules
│   └── formats/                  # Dossier contenant les formats d'encodage
│       ├── hex.c                 # Encodage/Décodage hexadécimal
│       └── base64.c              # Encodage/Décodage Base64
├── includes/                     # Fichiers d'en-tête (.h)
│   ├── args.h                    # Structures et fonctions pour les arguments
│   ├── args_handlers.h           # Gestionnaires spécifiques des arguments
│   ├── actions.h                 # Interfaces des actions disponibles
│   ├── action_dispatcher.h       # Dispatcher d'actions
│   ├── formats.h                 # Interfaces des formats d'encodage
│   ├── format_dispatcher.h       # Dispatcher de formats
│   ├── file.h                    # Gestion des fichiers
│   ├── errors.h                  # Énumération des codes d'erreur
│   └── help.h                    # Affichage de l'aide
├── builddir/                     # Répertoire de compilation (généré par Meson)
│   └── isenChef.exe              # Exécutable final
├── meson.build                   # Configuration de build Meson
├── README.md                     # Documentation du projet
├── help.md                       # Guide d'utilisation complet
├── input.txt                     # Fichier d'entrée exemple
└── output.txt                    # Fichier de sortie exemple

```

### Description

- **src/** : Contient tout le code source C
  - Les fichiers principaux gèrent les arguments, les fichiers, le dispatcher d'actions, le dispathcer de formats, les erreurs et les aides
  - Le dossier `actions/` contient les implémentations de chaque transformation/chiffrement
  - Le dossier `formats` contient les implémentations de chaque format disponible
  
- **includes/** : Contient les fichiers d'en-tête qui définissent les interfaces publiques

- **builddir/** : Répertoire généré par Meson lors de la compilation, contient les fichiers objets et l'exécutable final

- **meson.build** : Configuration du système de build pour Meson

---

## Détails des Actions

### Actions sans clé
- **uppercase** : Convertit tous les caractères en majuscules
- **lowercase** : Convertit tous les caractères en minuscules
- **reverse** : Inverse l'ordre des octets du fichier

### Actions avec clé
- **caesar** : Chiffrement César (clé numérique, peut être négative pour déchiffrer)
- **xor** : Chiffrement XOR (clé numérique ou texte)
- **rc4** : Chiffrement RC4 stream cipher (clé texte)

---

## Détails des Formats

- **bytes** : Format brut (défaut, pas de transformation)
- **hex** : Encodage hexadécimal
- **base64** : Encodage Base64

---

Pour plus de détails, consulter [help.md](https://github.com/maeldolium/isenChef/blob/master/help.md)

---

## Auteur

**[Maël](https://github.com/maeldolium)** - Projet réalisé dans le cadre de ma 3ème année d'école d'ingénieur.

