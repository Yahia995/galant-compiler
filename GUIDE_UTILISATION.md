# 📚 Guide d'Utilisation Complet - GALANT

## Table des Matières

1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Premiers Pas](#premiers-pas)
4. [Syntaxe Détaillée](#syntaxe-détaillée)
5. [Exemples Avancés](#exemples-avancés)
6. [Comprendre la Sortie](#comprendre-la-sortie)
7. [Dépannage](#dépannage)
8. [Bonnes Pratiques](#bonnes-pratiques)

---

## Introduction

### Qu'est-ce que GALANT ?

**GALANT** (GALe LANguage educaTif) est un compilateur minimaliste pour un langage de programmation **entièrement en français**.

#### Caractéristiques Principales

- 📝 **Extension** : `.gal`
- 🇫🇷 **Langage** : Français uniquement
- 🏗️ **Architecture** : Lexer → Parser → Sémantique → Exécution
- 🎓 **Objectif** : Apprentissage de la compilation

#### Pourquoi GALANT ?

- **Éducatif** : Comprendre comment fonctionne un compilateur
- **Simple** : Syntaxe minimaliste et intuitive
- **Français** : Pas de barrière linguistique pour les francophones
- **Complet** : Toutes les phases de compilation implémentées

---

## Installation

### Prérequis

Avant de commencer, assurez-vous d'avoir :

- **GCC** (version 4.8 ou supérieure)
- **Make** (GNU Make)
- **Terminal/Console** (Bash, PowerShell, CMD)

#### Vérifier les prérequis

```bash
# Vérifier GCC
gcc --version

# Vérifier Make
make --version
```

### Étapes d'Installation

#### 1. Télécharger le projet

```bash
git clone <votre-repo-url>
cd GALANT
```

#### 2. Compiler le projet

```bash
make
```

**Sortie attendue :**
```
  Compile: main.c
  Compile: lexer.c
  Compile: parser.c
  Compile: semantic.c
Compilation reussie. Executable: galant-compiler
```

#### 3. Vérifier l'installation

```bash
# Linux/Mac
ls -la galant-compiler

# Windows
dir galant-compiler.exe
```

#### 4. Premier test

```bash
./galant-compiler programme.gal
```

### Commandes Make Utiles

| Commande | Description |
|----------|-------------|
| `make` | Compiler le projet |
| `make clean` | Supprimer les fichiers compilés |
| `make run` | Compiler et exécuter `programme.gal` |
| `make help` | Afficher l'aide |

---

## Premiers Pas

### Créer Votre Premier Programme

#### Étape 1 : Créer un fichier

Créez un fichier nommé `hello.gal` :

```galant
# Mon premier programme GALANT
variable message = 42;
afficher(message);
```

#### Étape 2 : Exécuter

```bash
./galant-compiler hello.gal
```

#### Étape 3 : Observer le résultat

```
=== Execution ===
42
```

### Comprendre la Structure

Chaque programme GALANT suit cette structure :

```galant
# Commentaires (optionnel)

# 1. Déclarations de variables
variable x = 10;
variable y = 20;

# 2. Traitement (boucles, conditions)
tantque (x < y) {
  x = x + 1;
}

# 3. Affichage des résultats
afficher(x);
```

---

## Syntaxe Détaillée

### 1. Variables

#### Déclaration avec Initialisation

```galant
variable nom = valeur;
```

**Exemples :**
```galant
variable age = 25;
variable compteur = 0;
variable nombre = 100;
```

#### Déclaration sans Initialisation

```galant
variable nom;
```

⚠️ **Attention** : Utiliser une variable non initialisée provoque une erreur :
```
Erreur semantique: variable 'nom' utilisee avant initialisation
```

#### Réaffectation

```galant
variable x = 10;
x = 20;          # Modification de la valeur
x = x + 5;       # Utilisation dans une expression
```

#### Règles de Nommage

✅ **Autorisé :**
- Lettres : `a-z`, `A-Z`
- Chiffres : `0-9` (pas en premier caractère)
- Underscore : `_`

❌ **Interdit :**
- Espaces
- Caractères spéciaux (sauf `_`)
- Mots-clés du langage
- Commencer par un chiffre

**Exemples valides :**
```galant
variable nombre = 5;
variable nombre_total = 10;
variable compteur1 = 0;
variable _valeur = 100;
```

**Exemples invalides :**
```galant
variable 1nombre = 5;      # Commence par un chiffre
variable mon-nombre = 10;  # Contient un tiret
variable variable = 20;    # Mot-clé réservé
```

---

### 2. Opérateurs Arithmétiques

#### Addition (`+`)

```galant
variable a = 5;
variable b = 3;
variable somme = a + b;    # somme = 8
afficher(somme);
```

#### Soustraction (`-`)

```galant
variable difference = 10 - 3;  # difference = 7
afficher(difference);
```

#### Multiplication (`*`)

```galant
variable produit = 4 * 5;      # produit = 20
afficher(produit);
```

#### Division Entière (`/`)

```galant
variable quotient = 10 / 3;    # quotient = 3 (division entière)
afficher(quotient);
```

⚠️ **Division par zéro :**
```galant
variable x = 10 / 0;
# Erreur semantique: division par zero
```

#### Modulo (`%`)

```galant
variable reste = 10 % 3;       # reste = 1
afficher(reste);
```

#### Priorité des Opérateurs

1. **Haute priorité** : `*`, `/`, `%`
2. **Basse priorité** : `+`, `-`

```galant
variable resultat = 2 + 3 * 4;  # resultat = 14 (pas 20)
afficher(resultat);

variable avec_parentheses = (2 + 3) * 4;  # avec_parentheses = 20
afficher(avec_parentheses);
```

---

### 3. Opérateurs de Comparaison

| Opérateur | Signification | Exemple |
|-----------|---------------|---------|
| `==` | Égal | `x == 5` |
| `!=` | Différent | `x != 5` |
| `>` | Supérieur | `x > 5` |
| `<` | Inférieur | `x < 5` |
| `>=` | Supérieur ou égal | `x >= 5` |
| `<=` | Inférieur ou égal | `x <= 5` |

**Exemples :**

```galant
variable x = 10;

si (x == 10) {
  afficher(1);    # S'exécute
}

si (x != 5) {
  afficher(2);    # S'exécute
}

si (x > 5) {
  afficher(3);    # S'exécute
}

si (x <= 20) {
  afficher(4);    # S'exécute
}
```

---

### 4. Structures de Contrôle

#### Condition Simple (si)

```galant
si (condition) {
  # Instructions si la condition est vraie
}
```

**Exemple :**
```galant
variable age = 18;

si (age >= 18) {
  afficher(1);    # Affiche 1
}
```

#### Condition avec Alternative (si/sinon)

```galant
si (condition) {
  # Instructions si vraie
} sinon {
  # Instructions si fausse
}
```

**Exemple :**
```galant
variable nombre = 7;

si (nombre % 2 == 0) {
  afficher(0);    # Pair
} sinon {
  afficher(1);    # Impair - s'exécute
}
```

#### Conditions Imbriquées

```galant
variable note = 75;

si (note >= 90) {
  afficher(5);    # Excellent
} sinon {
  si (note >= 80) {
    afficher(4);  # Très bien
  } sinon {
    si (note >= 70) {
      afficher(3);  # Bien - s'exécute
    } sinon {
      afficher(2);  # Passable
    }
  }
}
```

---

### 5. Boucles (tantque)

#### Syntaxe de Base

```galant
tantque (condition) {
  # Instructions à répéter
}
```

#### Exemple Simple

```galant
variable i = 0;

tantque (i < 5) {
  afficher(i);
  i = i + 1;
}

# Affiche : 0, 1, 2, 3, 4
```

#### Boucle de Comptage

```galant
variable compteur = 1;

tantque (compteur <= 10) {
  afficher(compteur);
  compteur = compteur + 1;
}

# Affiche les nombres de 1 à 10
```

#### Boucles Imbriquées

```galant
variable i = 0;
variable j = 0;

tantque (i < 3) {
  j = 0;
  tantque (j < 2) {
    afficher(i * 10 + j);
    j = j + 1;
  }
  i = i + 1;
}

# Affiche : 0, 1, 10, 11, 20, 21
```

⚠️ **Attention aux boucles infinies :**
```galant
variable x = 0;
tantque (x < 10) {
  afficher(x);
  # ERREUR : x n'est jamais incrémenté !
  # Boucle infinie
}
```

---

### 6. Affichage

#### Afficher une Variable

```galant
variable x = 42;
afficher(x);      # Affiche : 42
```

#### Afficher une Expression

```galant
variable a = 5;
variable b = 3;
afficher(a + b);  # Affiche : 8
afficher(a * 2);  # Affiche : 10
```

#### Afficher un Nombre Littéral

```galant
afficher(100);    # Affiche : 100
afficher(0);      # Affiche : 0
```

#### Affichages Multiples

```galant
variable x = 10;
variable y = 20;
variable z = 30;

afficher(x);
afficher(y);
afficher(z);

# Affiche :
# 10
# 20
# 30
```

---

### 7. Commentaires

#### Commentaire sur une Ligne

```galant
# Ceci est un commentaire
variable x = 5;    # Commentaire en fin de ligne
```

#### Commentaires Multiples

```galant
# Première ligne de commentaire
# Deuxième ligne de commentaire
# Troisième ligne de commentaire
variable y = 10;
```

#### Bonnes Pratiques

```galant
# ============================================
# Programme : Calcul de factorielle
# Auteur : Votre Nom
# Date : 2024
# ============================================

# Initialisation des variables
variable n = 5;              # Nombre dont on calcule la factorielle
variable resultat = 1;       # Résultat final
variable i = 1;              # Compteur de boucle

# Calcul de la factorielle
tantque (i <= n) {
  resultat = resultat * i;
  i = i + 1;
}

# Affichage du résultat
afficher(resultat);
```

---

## Exemples Avancés

### Exemple 1 : Table de Multiplication

```galant
# Table de multiplication par 7
variable i = 1;
variable resultat = 0;

tantque (i <= 10) {
  resultat = 7 * i;
  afficher(resultat);
  i = i + 1;
}

# Affiche : 7, 14, 21, 28, 35, 42, 49, 56, 63, 70
```

### Exemple 2 : Somme des N Premiers Entiers

```galant
# Somme de 1 à 100
variable n = 100;
variable i = 1;
variable somme = 0;

tantque (i <= n) {
  somme = somme + i;
  i = i + 1;
}

afficher(somme);  # Affiche : 5050
```

### Exemple 3 : Puissance

```galant
# Calcul de 2^10
variable base = 2;
variable exposant = 10;
variable resultat = 1;
variable i = 0;

tantque (i < exposant) {
  resultat = resultat * base;
  i = i + 1;
}

afficher(resultat);  # Affiche : 1024
```

### Exemple 4 : Recherche de Maximum

```galant
# Trouver le plus grand nombre entre trois valeurs
variable a = 45;
variable b = 67;
variable c = 23;
variable max = 0;

# Comparer a et b
si (a > b) {
  max = a;
} sinon {
  max = b;
}

# Comparer max avec c
si (c > max) {
  max = c;
}

afficher(max);  # Affiche : 67
```

### Exemple 5 : Nombres Premiers (Test Simple)

```galant
# Vérifier si 17 est premier
variable n = 17;
variable i = 2;
variable est_premier = 1;

tantque (i < n) {
  si (n % i == 0) {
    est_premier = 0;
  }
  i = i + 1;
}

afficher(est_premier);  # Affiche : 1 (vrai)
```

### Exemple 6 : Suite de Fibonacci

```galant
# Les 10 premiers nombres de Fibonacci
variable n = 10;
variable i = 0;
variable a = 0;
variable b = 1;
variable temp = 0;

tantque (i < n) {
  afficher(a);
  temp = a + b;
  a = b;
  b = temp;
  i = i + 1;
}

# Affiche : 0, 1, 1, 2, 3, 5, 8, 13, 21, 34
```

---

## Comprendre la Sortie

### Structure de la Sortie

Lorsque vous exécutez un programme, le compilateur affiche quatre sections :

#### 1. Code Source

```
=== Code Source ===
variable x = 5;
afficher(x);
```

Le code source tel qu'il est lu depuis le fichier `.gal`.

#### 2. Analyse Lexicale

```
=== Analyse Lexicale ===
[v0] Nombre de tokens: 7
[  0] MOT_CLE         = 'variable' (mot-cle: VARIABLE)
[  1] IDENTIFICATEUR  = 'x'
[  2] PONCTUATION     = '='
[  3] NOMBRE          = '5' (valeur: 5)
[  4] PONCTUATION     = ';'
[  5] MOT_CLE         = 'afficher' (mot-cle: AFFICHER)
[  6] PONCTUATION     = '('
...
```

**Détails :**
- Liste de tous les tokens (jetons) détectés
- Type de chaque token
- Valeur associée
- Position dans le code

#### 3. Analyse Syntaxique (AST)

```
=== Analyse Syntaxique (AST) ===
PROGRAMME
  AFFECTATION [x]
    NOMBRE [5] (5)
  AFFICHAGE
    VARIABLE [x]
```

**Détails :**
- Arbre de Syntaxe Abstraite (AST)
- Structure hiérarchique du programme
- Relations entre les instructions

#### 4. Exécution

```
=== Execution ===
5
```

Le résultat de l'exécution du programme.

### Modes de Verbosité

Les messages `[v0]` indiquent les étapes internes :

```
[v0] Demarrage de l'analyse lexicale
[v0] Lexer cree
[v0] Lexer analyse
...
```

Ces messages aident à comprendre le processus de compilation.

---

## Dépannage

### Erreurs Courantes

#### 1. Fichier Non Trouvé

**Erreur :**
```
Erreur: impossible d'ouvrir le fichier 'programme.gal'
```

**Solutions :**
- Vérifiez le nom du fichier
- Vérifiez l'extension `.gal`
- Vérifiez le chemin d'accès
- Utilisez `ls` ou `dir` pour lister les fichiers

#### 2. Variable Non Déclarée

**Erreur :**
```
Erreur semantique: variable 'x' non declaree
```

**Solution :**
```galant
# MAUVAIS
afficher(x);  # x n'existe pas

# BON
variable x = 5;
afficher(x);
```

#### 3. Variable Non Initialisée

**Erreur :**
```
Erreur semantique: variable 'x' utilisee avant initialisation
```

**Solution :**
```galant
# MAUVAIS
variable x;
afficher(x);  # x n'a pas de valeur

# BON
variable x = 0;
afficher(x);
```

#### 4. Division par Zéro

**Erreur :**
```
Erreur semantique: division par zero
```

**Solution :**
```galant
# MAUVAIS
variable x = 10 / 0;

# BON
variable diviseur = 5;
si (diviseur != 0) {
  variable x = 10 / diviseur;
  afficher(x);
}
```

#### 5. Erreur de Syntaxe

**Erreur :**
```
Erreur syntaxique a la ligne X
```

**Causes courantes :**
- Oubli du point-virgule `;`
- Parenthèses non fermées
- Accolades non équilibrées
- Mot-clé mal orthographié

**Exemple :**
```galant
# MAUVAIS
variable x = 5  # Manque le point-virgule

# BON
variable x = 5;
```

---

## Bonnes Pratiques

### 1. Nommage des Variables

✅ **Bon :**
```galant
variable nombre_etudiants = 25;
variable somme_totale = 1000;
variable compteur_iterations = 0;
```

❌ **Mauvais :**
```galant
variable n = 25;      # Peu explicite
variable x = 1000;    # Peu explicite
variable i = 0;       # OK seulement pour les boucles courtes
```

### 2. Indentation

✅ **Bon :**
```galant
si (x > 0) {
  tantque (x < 10) {
    afficher(x);
    x = x + 1;
  }
}
```

❌ **Mauvais :**
```galant
si (x > 0) {
tantque (x < 10) {
afficher(x);
x = x + 1;
}
}
```

### 3. Commentaires

✅ **Bon :**
```galant
# Calcul de la moyenne de trois notes
variable note1 = 15;
variable note2 = 18;
variable note3 = 12;
variable moyenne = (note1 + note2 + note3) / 3;
```

❌ **Mauvais :**
```galant
variable n1 = 15;  # note 1
variable n2 = 18;  # note 2
variable n3 = 12;  # note 3
variable m = (n1 + n2 + n3) / 3;  # moyenne
```

### 4. Organisation du Code

```galant
# ====================================
# En-tête et description
# ====================================

# Déclarations
variable x = 0;
variable y = 0;
variable resultat = 0;

# Traitement principal
tantque (x < 10) {
  y = x * 2;
  resultat = resultat + y;
  x = x + 1;
}

# Affichage final
afficher(resultat);
```

### 5. Éviter les Boucles Infinies

✅ **Bon :**
```galant
variable i = 0;
tantque (i < 10) {
  afficher(i);
  i = i + 1;  # N'oubliez pas d'incrémenter !
}
```

❌ **Mauvais :**
```galant
variable i = 0;
tantque (i < 10) {
  afficher(i);
  # Oubli de l'incrémentation -> boucle infinie !
}
```

### 6. Tester Progressivement

```galant
# Étape 1 : Tester les variables
variable x = 5;
afficher(x);

# Étape 2 : Ajouter la logique
# tantque (...) { ... }

# Étape 3 : Tester le résultat final
```

---

## Template de Démarrage

Utilisez ce modèle pour commencer un nouveau programme :

```galant
# ============================================
# Nom du programme : [Votre titre]
# Description : [Ce que fait le programme]
# Auteur : [Votre nom]
# Date : [Date]
# ============================================

# --- Déclaration des variables ---
variable x = 0;
variable y = 0;
variable resultat = 0;

# --- Traitement principal ---
tantque (x < 10) {
  # Votre logique ici
  x = x + 1;
}

# --- Affichage des résultats ---
afficher(resultat);
```

---

## Ressources Supplémentaires

- **README.md** - Vue d'ensemble du projet
- **ARCHITECTURE.md** - Documentation technique détaillée
- **Exemples** - Dossier avec programmes d'exemple

---

## Aide et Support

### Commandes Utiles

```bash
# Voir l'aide de Make
make help

# Nettoyer et recompiler
make clean && make

# Exécuter le programme par défaut
make run
```

### Débogage

1. **Vérifiez la section "Analyse Lexicale"** pour voir si les tokens sont corrects
2. **Vérifiez l'AST** pour voir si la structure est bonne
3. **Lisez les messages d'erreur** attentivement
4. **Testez avec un programme simple** d'abord

---

**Bon apprentissage avec GALANT ! 🚀📚**