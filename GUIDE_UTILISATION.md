# 📚 Guide d'Utilisation - GALANT

## Qu'est-ce que GALANT ?

**GALANT** = **GA**Le **LAN**guage e**N**ducaTif

Un compilateur minimaliste pour un langage de programmation **entièrement en français**.

- **Extension de fichier** : `.gal`
- **Langage** : Français uniquement
- **Architecture** : Lexer → Parser → Sémantique → Exécution

---

## Installation et Compilation

### Prérequis
- GCC (ou tout compilateur C compatible)
- Make
- Terminal/Console

### Étapes

\`\`\`bash
# 1. Compiler le projet
make

# 2. Vérifier que l'exécutable est créé
ls -la galant-compiler

# 3. Exécuter un programme
./galant-compiler programme.gal
\`\`\`

---

## Syntaxe du Langage GALANT

### 1. Déclaration et Affectation

Déclarer une variable et lui assigner une valeur :

\`\`\`galant
variable x = 5;
variable prenom = 10;  # N'importe quel nom
\`\`\`

Modifier la valeur :

\`\`\`galant
x = 20;
y = x + 5;
\`\`\`

### 2. Affichage

Afficher des valeurs à l'écran :

\`\`\`galant
afficher(x);
afficher(y + 3);
afficher(42);
\`\`\`

### 3. Opérateurs Arithmétiques

\`\`\`galant
variable a = 10;
variable b = 3;

afficher(a + b);      # Addition : 13
afficher(a - b);      # Soustraction : 7
afficher(a * b);      # Multiplication : 30
afficher(a / b);      # Division entière : 3
afficher(a % b);      # Modulo (reste) : 1
\`\`\`

### 4. Conditions (SI / SINON)

\`\`\`galant
variable age = 18;

si (age >= 18) {
  afficher(1);  # Majeur
} sinon {
  afficher(0);  # Mineur
}
\`\`\`

**Opérateurs de comparaison :**
- `==` : Égal
- `!=` : Différent
- `>` : Supérieur à
- `<` : Inférieur à
- `>=` : Supérieur ou égal
- `<=` : Inférieur ou égal

### 5. Boucles (TANTQUE)

\`\`\`galant
variable i = 0;

tantque (i < 5) {
  afficher(i);
  i = i + 1;
}
\`\`\`

### 6. Commentaires

\`\`\`galant
# Ceci est un commentaire
variable x = 10;  # Affecte 10 à x
# Les commentaires sont ignorés
\`\`\`

---

## Exemples Complets

### Exemple 1 : Boucle Simple

**Fichier : exemple1.gal**
\`\`\`galant
variable i = 0;
tantque (i < 5) {
  afficher(i);
  i = i + 1;
}
\`\`\`

\`\`\`bash
./galant-compiler exemple1.gal
\`\`\`

**Sortie :**
\`\`\`
0
1
2
3
4
\`\`\`

---

### Exemple 2 : Nombres Pairs/Impairs

**Fichier : exemple2.gal**
\`\`\`galant
variable x = 0;
tantque (x < 10) {
  si (x % 2 == 0) {
    afficher(x);
  } sinon {
    afficher(-1);
  }
  x = x + 1;
}
\`\`\`

**Sortie :**
\`\`\`
0
-1
2
-1
4
-1
6
-1
8
-1
\`\`\`

---

### Exemple 3 : Factorielle

**Fichier : factorielle.gal**
\`\`\`galant
variable n = 5;
variable resultat = 1;
variable i = 1;

tantque (i <= n) {
  resultat = resultat * i;
  i = i + 1;
}

afficher(resultat);
\`\`\`

**Sortie :**
\`\`\`
120
\`\`\`

---

### Exemple 4 : Imbrication SI/SINON

\`\`\`galant
variable score = 75;

si (score >= 80) {
  afficher(1);  # Excellent
} sinon {
  si (score >= 60) {
    afficher(2);  # Bien
  } sinon {
    afficher(3);  # À améliorer
  }
}
\`\`\`

---

## Comprendre la Sortie

Quand vous exécutez `./galant-compiler programme.gal`, vous verrez :

**Section 1 : Code Source**
\`\`\`
===== CODE SOURCE =====
variable x = 0;
tantque (x < 5) { ... }
\`\`\`

**Section 2 : Analyse Lexicale**
\`\`\`
===== TOKENS LEXICAUX =====
[  0] MOT_CLE         = 'variable'
[  1] IDENTIFICATEUR  = 'x'
[  2] PONCTUATION     = '='
[  3] NOMBRE          = '0' (valeur: 0)
\`\`\`

**Section 3 : Analyse Syntaxique**
\`\`\`
===== ARBRE DE SYNTAXE ABSTRAITE =====
Programme
  Instruction_Affectation (x = 0)
  Instruction_Boucle
    Condition: (x < 5)
\`\`\`

**Section 4 : Exécution**
\`\`\`
===== EXÉCUTION =====
Résultat d'exécution:
0
1
2
3
4
\`\`\`

---

## Mots-Clés Réservés

| Mot-clé | Utilité |
|---------|---------|
| `variable` | Déclarer une variable |
| `afficher` | Afficher une valeur |
| `si` | Condition IF |
| `sinon` | Condition ELSE |
| `tantque` | Boucle WHILE |

---

## Commandes Make

\`\`\`bash
make              # Compiler
make clean        # Nettoyer
make run          # Compiler et exécuter programme.gal
make help         # Afficher l'aide
\`\`\`

---

## Conseils et Bonnes Pratiques

1. **Toujours terminer par `;`** (sauf les blocs `{}`)
2. **Déclarer avant d'utiliser** avec `variable`
3. **Noms explicites** : `age` plutôt que `a`
4. **Indenter le code** pour lisibilité
5. **Commenter** vos programmes
6. **Tester progressivement**

---

## Dépannage

### Erreur : "Fichier non trouvé"
\`\`\`
Erreur: impossible d'ouvrir le fichier
\`\`\`
→ Vérifiez le chemin et l'extension `.gal`

### Erreur : "Variable non déclarée"
\`\`\`
Erreur sémantique: variable 'x' non déclarée
\`\`\`
→ Utilisez `variable x = valeur;` avant utilisation

### Erreur : "Division par zéro"
\`\`\`
Erreur sémantique: division par zéro
\`\`\`
→ Évitez les divisions par 0

### Erreur : "Syntaxe invalide"
\`\`\`
Erreur syntaxique à la ligne X
\`\`\`
→ Vérifiez la grammaire française

---

## Template Prêt à l'Emploi

Commencez avec ce modèle :

\`\`\`galant
# Mon programme GALANT

# Déclarations
variable x = 0;
variable resultat = 0;

# Traitement
tantque (x < 10) {
  si (x % 2 == 0) {
    afficher(x);
  }
  x = x + 1;
}

# Résultat
afficher(resultat);
\`\`\`

---

## Ressources

- Compilateur : `galant-compiler`
- Exemples : `programme.gal`, `exemple2.gal`
- Source : Code C modulaire (lexer, parser, semantic)

Bon codage avec GALANT ! 🚀
