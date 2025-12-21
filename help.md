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
```
Bonjour le monde
```

**Après :**
```
BONJOUR LE MONDE
```

---

### 2. **lowercase**
Convertit tout le texte en minuscules.

**Exemple :**
```bash
isenChef.exe --in document.txt --out output.txt --action lowercase
```

**Avant :**
```
HELLO WORLD
```

**Après :**
```
hello world
```

---

### 3. **hex**
Convertit le texte en représentation hexadécimale.

**Exemple :**
```bash
isenChef.exe --in message.txt --out output.txt --action hex
```

**Avant :**
```
ABC
```

**Après :**
```
414243
```

> ℹ️ Chaque caractère est représenté par deux chiffres hexadécimaux.

---

### 4. **base64**
Encode le contenu en Base64.

**Exemple :**
```bash
isenChef.exe --in data.txt --out output.txt --action base64
```

**Avant :**
```
Hello World
```

**Après :**
```
SGVsbG8gV29ybGQ=
```

---

## 🔗 Chaîner plusieurs actions

Vous pouvez appliquer plusieurs actions successivement en utilisant plusieurs options `--action` :

```bash
isenChef.exe --in input.txt --out output.txt --action uppercase --action hex
```

Cet exemple :
1. Convertit le texte en majuscules
2. Puis encode le résultat en hexadécimal

---

## 📝 Exemples pratiques

### Exemple 1 : Encoder un message en Base64

```bash
isenChef.exe --in secret.txt --out encoded.txt --action base64
```

### Exemple 2 : Normaliser un texte (minuscules + hex)

```bash
isenChef.exe --in data.txt --out processed.txt --action lowercase --action hex
```

### Exemple 3 : Transformer plusieurs fichiers

```bash
REM Convertir fichier 1
isenChef.exe --in file1.txt --out file1_upper.txt --action uppercase

REM Convertir fichier 2
isenChef.exe --in file2.txt --out file2_encoded.txt --action base64
```

---

## ⚠️ Notes importantes

- **Les fichiers d'entrée et de sortie doivent être spécifiés** avec `--in` et `--out`
- **Au moins une action est obligatoire**
- Les chemins peuvent être relatifs ou absolais
- Les fichiers sont lus et écris en entier en mémoire
- Les actions sont appliquées dans l'ordre où elles sont spécifiées

---

## 🐛 Dépannage

### Erreur : "Le fichier d'entrée n'existe pas"
✅ Vérifiez que le chemin du fichier `--in` est correct et que le fichier existe.

### Erreur : "L'action est inconnue"
✅ Vérifiez l'orthographe de l'action. Les actions valides sont :
- `uppercase`
- `lowercase`
- `hex`
- `base64`

### Erreur : "Arguments manquants"
✅ Assurez-vous d'avoir spécifié :
- `--in <fichier_entree>`
- `--out <fichier_sortie>`
- `--action <action>`

---

## 📚 Formats supportés

Les fichiers peuvent être de n'importe quel format texte :
- `.txt` - Fichiers texte brut
- `.log` - Fichiers journaux
- `.csv` - Fichiers de données
- `.json` - Fichiers JSON
- `.xml` - Fichiers XML
- Tout autre format texte

---

## 💡 Cas d'usage courants

| Besoin | Commande |
|--------|----------|
| Convertir en majuscules | `--action uppercase` |
| Convertir en minuscules | `--action lowercase` |
| Encoder en hexadécimal | `--action hex` |
| Encoder en Base64 | `--action base64` |
| Plusieurs transformations | `--action action1 --action action2` |

---

**Version 1.0** - IsenChef
