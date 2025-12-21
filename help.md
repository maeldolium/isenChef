# isenChef - Outil de transformation de fichiers

*inspiré par CyberChef*  
**Auteur : Maël**

---

## UTILISATION

```
./isenChef.exe [OPTIONS]
```

## SYNTAXE GÉNÉRALE

```
./isenChef.exe --in <fichier_entrée> --input-format <format> \
       [--action <action> [--key <clé>]] \
       --out <fichier_sortie> --output-format <format>
```

## OPTIONS DISPONIBLES

- `--in <fichier>`              Chemin du fichier d'entrée
- `--out <fichier>`             Chemin du fichier de sortie
- `--input-format <fmt>`        Format d'entrée (voir formats ci-dessous)
- `--output-format <fmt>`       Format de sortie (voir formats ci-dessous)
- `--action <action>`           Action à appliquer (optionnel)
- `--key <clé>`                 Clé pour les actions qui en nécessitent une (dépend de l'action)
- `--help`                      Affiche ce message d'aide

## FORMATS SUPPORTÉS

- `bytes`    - Octets bruts (par défaut)
- `hex`      - Codage hexadécimal
- `base64`   - Codage Base64

### Note importante
- Les formats d'entrée sont décodés en octets avant l'action
- Les formats de sortie sont encodés après l'action

## ACTIONS SUPPORTÉES

### Sans clé
- `uppercase`   - Convertir le texte en majuscules
- `lowercase`   - Convertir le texte en minuscules
- `reverse`     - Inverser le contenu du fichier

### Avec clé
- `caesar`      - Chiffre de César
- `xor`         - Chiffrement XOR
- `rc4`         - Chiffrement RC4

## GESTION DES CLÉS

- Les clés numériques sont supportées pour caesar et xor
- Les clés numériques signées sont permises pour caesar (valeur négative = déchiffrement)
- Les clés texte sont supportées pour xor et rc4

## CHEMINS DE FICHIERS

- Les chemins sont relatifs au répertoire de build (`builddir/`)
- Pour accéder à un fichier à la racine du projet : utiliser `../`
- Exemples de chemins :
  - Fichier dans `builddir/` : `mon_fichier.txt`
  - Fichier à la racine : `../mon_fichier.txt`
  - Fichier dans un sous-dossier : `../dossier/mon_fichier.txt`

## GESTION DES ERREURS

- Les arguments invalides sont signalés avec des messages explicites
- Les fichiers manquants et les actions inconnues sont détectés
- Les encodages invalides (hex/base64) sont rejetés

## POUR PLUS D'INFORMATIONS

Consultez le fichier README.md pour la documentation détaillée
