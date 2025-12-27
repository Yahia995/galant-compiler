# 🚀 GALANT - Compilateur Éducatif

**GALANT** = **GA**Le **LAN**guage educa**T**if

Un compilateur complet en C pour un langage de programmation minimaliste, **entièrement en français**.

---

## ✨ Caractéristiques

- ✅ **Syntaxe 100% française** - Tous les mots-clés en français
- ✅ **Extension `.gal`** - Format de fichier dédié
- ✅ **Architecture complète** - Lexer → Parser → Sémantique
- ✅ **Fonctionnalités complètes** - Variables, conditions, boucles, opérateurs
- ✅ **Commentaires** - Support des commentaires avec `#`
- ✅ **Code modulaire** - Structure C propre et bien organisée
- ✅ **Gestion d'erreurs** - Messages d'erreur clairs et informatifs

---

## 🚀 Installation Rapide

### Prérequis
- GCC (ou tout compilateur C compatible)
- Make
- Terminal/Console

### Compilation

```bash
# Cloner le projet
git clone <votre-repo>
cd GALANT

# Compiler
make

# Vérifier l'exécutable
ls -la galant-compiler
```

### Exécution

```bash
# Exécuter un programme GALANT
./galant-compiler programme.gal

# Ou utiliser make run (exécute programme.gal par défaut)
make run
```

---

## 📖 Guide Rapide du Langage

### Variables

```galant
variable x = 5;          # Déclaration avec initialisation
variable nom = 10;       # N'importe quel nom valide
variable y;              # Déclaration sans initialisation (erreur si utilisée)
x = 20;                  # Réaffectation
```

### Affichage

```galant
afficher(x);             # Affiche la valeur de x
afficher(y + 3);         # Affiche le résultat d'une expression
afficher(42);            # Affiche un nombre littéral
```

### Opérateurs Arithmétiques

```galant
variable a = 10;
variable b = 3;

afficher(a + b);         # Addition : 13
afficher(a - b);         # Soustraction : 7
afficher(a * b);         # Multiplication : 30
afficher(a / b);         # Division entière : 3
afficher(a % b);         # Modulo (reste) : 1
```

### Conditions (si/sinon)

```galant
variable age = 18;

si (age >= 18) {
  afficher(1);           # Majeur
} sinon {
  afficher(0);           # Mineur
}
```

**Opérateurs de comparaison :**
- `==` : Égal
- `!=` : Différent
- `>` : Supérieur
- `<` : Inférieur
- `>=` : Supérieur ou égal
- `<=` : Inférieur ou égal

### Boucles (tantque)

```galant
variable i = 0;

tantque (i < 5) {
  afficher(i);
  i = i + 1;
}
# Affiche : 0, 1, 2, 3, 4
```

### Commentaires

```galant
# Ceci est un commentaire
variable x = 10;         # Commentaire en fin de ligne
# Les commentaires sont ignorés par le compilateur
```

---

## 💡 Exemples Complets

### Exemple 1 : Boucle Simple

**Fichier : `exemple1.gal`**

```galant
# Affiche les nombres de 0 à 4
variable i = 0;

tantque (i < 5) {
  afficher(i);
  i = i + 1;
}
```

**Exécution :**
```bash
./galant-compiler exemple1.gal
```

**Sortie :**
```
0
1
2
3
4
```

---

### Exemple 2 : Factorielle

**Fichier : `exemple2.gal`**

```galant
# Calcul de 5! (factorielle)
variable n = 5;
variable resultat = 1;
variable i = 1;

tantque (i <= n) {
  resultat = resultat * i;
  i = i + 1;
}

afficher(resultat);
```

**Sortie :**
```
120
```

---

### Exemple 3 : Nombres Pairs

**Fichier : `exemple3.gal`**

```galant
# Affiche les nombres pairs de 0 à 10
variable x = 0;

tantque (x <= 10) {
  si (x % 2 == 0) {
    afficher(x);
  }
  x = x + 1;
}
```

**Sortie :**
```
0
2
4
6
8
10
```

---

### Exemple 4 : Conditions Imbriquées

**Fichier : `exemple4.gal`**

```galant
# Évaluation d'une note
variable score = 75;

si (score >= 80) {
  afficher(1);           # Excellent
} sinon {
  si (score >= 60) {
    afficher(2);         # Bien
  } sinon {
    afficher(3);         # À améliorer
  }
}
```

---

## 🏗️ Architecture du Projet

```
GALANT/
├── main.c              # Point d'entrée du compilateur
├── lexer.c / lexer.h   # Analyse lexicale (tokenization)
├── parser.c / parser.h # Analyse syntaxique (AST)
├── semantic.c / semantic.h # Analyse sémantique et exécution
├── Makefile            # Configuration de compilation
├── README.md           # Ce fichier
├── GUIDE_UTILISATION.md # Guide complet en français
├── ARCHITECTURE.md     # Documentation technique détaillée
├── programme.gal       # Exemple de programme
└── exemple2.gal        # Exemple factorielle
```

### Phases de Compilation

```
Code Source (.gal)
        ↓
  [ANALYSE LEXICALE]
    Génère les tokens
        ↓
[ANALYSE SYNTAXIQUE]
   Construit l'AST
        ↓
[ANALYSE SÉMANTIQUE]
  Vérifie et exécute
        ↓
     Résultat
```

---

## 🎯 Mots-Clés du Langage

| Mot-clé | Description |
|---------|-------------|
| `variable` | Déclarer une variable |
| `afficher` | Afficher une valeur |
| `si` | Condition IF |
| `sinon` | Condition ELSE |
| `tantque` | Boucle WHILE |

---

## ⚙️ Commandes Make

```bash
make              # Compiler le projet
make clean        # Nettoyer les fichiers compilés
make run          # Compiler et exécuter programme.gal
make help         # Afficher l'aide
```

---

## 📊 Sortie du Compilateur

Lorsque vous exécutez un programme, le compilateur affiche :

### 1. Code Source
```
=== Code Source ===
variable x = 5;
...
```

### 2. Analyse Lexicale
```
=== Analyse Lexicale ===
[  0] MOT_CLE         = 'variable'
[  1] IDENTIFICATEUR  = 'x'
[  2] PONCTUATION     = '='
[  3] NOMBRE          = '5'
...
```

### 3. Arbre de Syntaxe Abstraite
```
=== Analyse Syntaxique (AST) ===
PROGRAMME
  AFFECTATION [x]
    NOMBRE [5] (5)
...
```

### 4. Exécution
```
=== Execution ===
5
```

---

## 🐛 Gestion des Erreurs

Le compilateur détecte et signale :

### Erreurs Lexicales
- Caractères non reconnus
- Tokens invalides

### Erreurs Syntaxiques
- Erreurs de grammaire
- Instructions mal formées
- Parenthèses non équilibrées

### Erreurs Sémantiques
- **Variable non déclarée**
  ```
  Erreur semantique: variable 'x' non declaree
  ```
  
- **Variable non initialisée**
  ```
  Erreur semantique: variable 'x' utilisee avant initialisation
  ```
  
- **Division par zéro**
  ```
  Erreur semantique: division par zero
  ```

---

## 📚 Documentation Complète

- **[GUIDE_UTILISATION.md](GUIDE_UTILISATION.md)** - Guide complet avec tous les détails
- **[ARCHITECTURE.md](ARCHITECTURE.md)** - Documentation technique approfondie

---

## 🎓 Utilisation Éducative

Ce compilateur est conçu pour l'apprentissage :

- **Comprendre** les phases de compilation
- **Expérimenter** avec un vrai compilateur
- **Apprendre** les structures de données (tokens, AST)
- **Découvrir** l'analyse sémantique et l'exécution

---

## 🤝 Contribution

Les contributions sont les bienvenues ! N'hésitez pas à :
- Signaler des bugs
- Proposer de nouvelles fonctionnalités
- Améliorer la documentation
- Ajouter des exemples

---

## 📝 Licence

Libre d'utilisation à titre éducatif.

---

## 🎯 Fonctionnalités Futures Possibles

- [ ] Support des fonctions
- [ ] Tableaux
- [ ] Chaînes de caractères
- [ ] Opérateurs logiques (`et`, `ou`, `non`)
- [ ] Boucle `pour`
- [ ] Génération de code assembleur
- [ ] Débogueur intégré

---

## 📞 Support

Pour toute question ou problème :
1. Consultez d'abord `GUIDE_UTILISATION.md`
2. Vérifiez `ARCHITECTURE.md` pour les détails techniques
3. Ouvrez une issue sur GitHub

---

**Bon codage avec GALANT ! 🚀🎓**