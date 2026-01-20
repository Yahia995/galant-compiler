# 🧠 Architecture du Compilateur GALANT

<div align="center">

![Architecture](https://img.shields.io/badge/GALANT-Architecture-purple?style=for-the-badge&logo=hackthebox&logoColor=white)
[![Complexité](https://img.shields.io/badge/Complexité-O(n)-green?style=for-the-badge)](.)
[![Langage](https://img.shields.io/badge/Langage-C99-orange?style=for-the-badge&logo=c)](.)

*Documentation technique complète du compilateur éducatif GALANT*

</div>

---

## 📑 Table des Matières

| 🔷 Section | 📝 Description |
|-----------|---------------|
| [🌐 Vue d'Ensemble](#-vue-densemble) | Architecture globale |
| [🔍 Phase 1 : Lexer](#-phase-1--analyse-lexicale) | Analyse lexicale (tokens) |
| [🌳 Phase 2 : Parser](#-phase-2--analyse-syntaxique) | Analyse syntaxique (AST) |
| [✅ Phase 3 : Semantic](#-phase-3--analyse-sémantique) | Analyse sémantique et exécution |
| [🎯 Module Principal](#-module-principal) | Point d'entrée (main.c) |
| [💾 Gestion Mémoire](#-gestion-mémoire) | Allocation et libération |
| [🐛 Gestion des Erreurs](#-gestion-des-erreurs) | Détection et traitement |
| [📊 Performance](#-complexité-et-performance) | Analyse de complexité |

---

## 🌐 Vue d'Ensemble

### 🏗️ Architecture Globale

```mermaid
graph TB
    A["📝 Code Source<br/>.gal"] --> B["🔍 Phase 1<br/>LEXER<br/>Tokenization"]
    B --> C["🌳 Phase 2<br/>PARSER<br/>AST Construction"]
    C --> D["✅ Phase 3<br/>SEMANTIC<br/>Execution"]
    D --> E["📤 Résultat"]
    
    B -.->|Erreur| F["❌ Erreur Lexicale"]
    C -.->|Erreur| G["❌ Erreur Syntaxique"]
    D -.->|Erreur| H["❌ Erreur Sémantique"]
    
    style A fill:#e3f2fd,stroke:#1976d2,stroke-width:3px,color:#000
    style B fill:#fff3e0,stroke:#f57c00,stroke-width:3px,color:#000
    style C fill:#f3e5f5,stroke:#7b1fa2,stroke-width:3px,color:#000
    style D fill:#e8f5e9,stroke:#388e3c,stroke-width:3px,color:#000
    style E fill:#fff9c4,stroke:#f57f17,stroke-width:3px,color:#000
    style F fill:#ffcdd2,stroke:#c62828,color:#000
    style G fill:#ffcdd2,stroke:#c62828,color:#000
    style H fill:#ffcdd2,stroke:#c62828,color:#000
```

### 🎯 Principes de Conception

<table>
<tr>
<td width="50%">

#### 🧩 Modularité
- Chaque phase est indépendante
- Interfaces claires entre modules
- Facilite la maintenance et l'évolution

</td>
<td width="50%">

#### 🔬 Clarté
- Code lisible et bien commenté
- Nommage explicite
- Documentation intégrée

</td>
</tr>
<tr>
<td width="50%">

#### 🛡️ Robustesse
- Gestion complète des erreurs
- Validation à chaque étape
- Messages d'erreur informatifs

</td>
<td width="50%">

#### 🎓 Éducatif
- Structure facile à comprendre
- Commentaires pédagogiques
- Exemples intégrés

</td>
</tr>
</table>

---

## 🔍 Phase 1 : Analyse Lexicale

### 🎯 Objectif

> Transformer le code source en une séquence de **tokens** (jetons lexicaux)

### 📁 Fichiers

| Fichier | Rôle |
|---------|------|
| `lexer.c` | 🔧 Implémentation |
| `lexer.h` | 📋 Interface et structures |

### 🏗️ Structures de Données

#### 1️⃣ TokenType - Types de Tokens

```c
typedef enum {
    TOKEN_NOMBRE,           // 42, 100, -5
    TOKEN_IDENTIFICATEUR,   // x, compteur, somme
    TOKEN_MOT_CLE,         // variable, si, tantque
    TOKEN_OPERATEUR_ARITH, // +, -, *, /, %
    TOKEN_OPERATEUR_COMP,  // ==, !=, >, <, >=, <=
    TOKEN_PONCTUATION,     // ;, (, ), {, }, =
    TOKEN_EOF,             // Fin de fichier
    TOKEN_ERREUR          // Token invalide
} TokenType;
```

#### 2️⃣ MotCle - Mots-clés du Langage

```c
typedef enum {
    KW_VARIABLE,  // variable
    KW_AFFICHER,  // afficher
    KW_SI,        // si
    KW_SINON,     // sinon
    KW_TANTQUE,   // tantque
    KW_NONE       // Pas un mot-clé
} MotCle;
```

#### 3️⃣ Token - Structure d'un Token

```c
typedef struct {
    TokenType type;        // Type du token
    char* valeur;         // Texte du token
    int ligne;            // Numéro de ligne
    int colonne;          // Position dans la ligne
    MotCle mot_cle;       // Si c'est un mot-clé
    int valeur_nombre;    // Si c'est un nombre
} Token;
```

**Représentation visuelle :**

```
┌─────────────────────────────────────┐
│ Token                               │
├─────────────────────────────────────┤
│ type:    TOKEN_MOT_CLE              │
│ valeur:  "variable"                 │
│ ligne:   1                          │
│ colonne: 1                          │
│ mot_cle: KW_VARIABLE                │
└─────────────────────────────────────┘
```

#### 4️⃣ Lexer - Structure Principale

```c
typedef struct {
    const char* source;   // Code source
    size_t pos;          // Position actuelle
    int ligne;           // Ligne actuelle
    int colonne;         // Colonne actuelle
    Token* tokens;       // Tableau de tokens
    int nb_tokens;       // Nombre de tokens
    int capacite;        // Capacité du tableau
} Lexer;
```

### ⚙️ Fonctions Principales

#### 🔨 Création du Lexer

```c
Lexer* lexer_creer(const char* source)
```

**Responsabilités :**
- ✅ Allouer la mémoire pour le lexer
- ✅ Initialiser la position à 0
- ✅ Créer le tableau de tokens (capacité : 100)

**Complexité :** `O(1)`

#### 🔍 Analyse Lexicale

```c
void lexer_analyser(Lexer* lexer)
```

**Algorithme détaillé :**

```mermaid
graph TD
    A[Début] --> B{Fin du fichier?}
    B -->|Non| C[Lire caractère]
    B -->|Oui| Z[Ajouter TOKEN_EOF]
    
    C --> D{Type?}
    D -->|Espace/\n| B
    D -->|#| E[Ignorer commentaire]
    D -->|Chiffre| F[lire_nombre]
    D -->|Lettre| G[lire_identificateur]
    D -->|Opérateur| H[lire_operateur]
    D -->|Ponctuation| I[Créer token]
    D -->|Autre| J[TOKEN_ERREUR]
    
    E --> B
    F --> K[Ajouter token]
    G --> K
    H --> K
    I --> K
    J --> K
    K --> B
    
    Z --> W[Fin]
    
    style A fill:#4caf50,color:#fff
    style W fill:#4caf50,color:#fff
    style J fill:#f44336,color:#fff
```

**Pseudo-code :**

```
TANT QUE pas fin du fichier :
    caractère ← lire_caractère()
    
    SI caractère est un espace ou \n :
        ignorer et continuer
    
    SINON SI caractère est '#' :
        ignorer jusqu'à fin de ligne (commentaire)
    
    SINON SI caractère est un chiffre :
        lire_nombre()
    
    SINON SI caractère est une lettre :
        lire_identificateur()
        vérifier si c'est un mot-clé
    
    SINON SI caractère est un opérateur (+, -, *, /, %, etc.) :
        lire_operateur()
        gérer les opérateurs doubles (==, !=, <=, >=)
    
    SINON SI caractère est une ponctuation :
        créer token de ponctuation
    
    SINON :
        créer TOKEN_ERREUR

AJOUTER TOKEN_EOF à la fin
```

**Complexité :** `O(n)` où n = longueur du code source

### 📊 Exemple de Tokenization

**Entrée :**
```galant
variable x = 5;
```

**Processus :**

```mermaid
graph LR
    A["variable"] --> B["x"]
    B --> C["="]
    C --> D["5"]
    D --> E[";"]
    
    style A fill:#f3e5f5
    style B fill:#e1f5ff
    style C fill:#fff3e0
    style D fill:#c8e6c9
    style E fill:#fff9c4
```

**Sortie (Tokens) :**

| Index | Type | Valeur | Détails |
|-------|------|--------|---------|
| `[0]` | `TOKEN_MOT_CLE` | `"variable"` | KW_VARIABLE |
| `[1]` | `TOKEN_IDENTIFICATEUR` | `"x"` | - |
| `[2]` | `TOKEN_PONCTUATION` | `"="` | - |
| `[3]` | `TOKEN_NOMBRE` | `"5"` | valeur: 5 |
| `[4]` | `TOKEN_PONCTUATION` | `";"` | - |
| `[5]` | `TOKEN_EOF` | `""` | - |

---

## 🌳 Phase 2 : Analyse Syntaxique

### 🎯 Objectif

> Construire un **Arbre de Syntaxe Abstraite (AST)** représentant la structure du programme

### 📁 Fichiers

| Fichier | Rôle |
|---------|------|
| `parser.c` | 🔧 Implémentation |
| `parser.h` | 📋 Interface et structures |

### 🏗️ Structures de Données

#### 1️⃣ ASTNodeType - Types de Nœuds

```c
typedef enum {
    AST_PROGRAMME,       // Nœud racine
    AST_AFFECTATION,     // x = expr
    AST_AFFICHAGE,       // afficher(expr)
    AST_CONDITION,       // si (cond) {...} sinon {...}
    AST_BOUCLE,          // tantque (cond) {...}
    AST_BLOC,            // { instructions }
    AST_EXPRESSION,      // Expression générique
    AST_NOMBRE,          // 42
    AST_VARIABLE,        // x
    AST_OPERATEUR,       // +, -, *, /, %
    AST_CONDITION_EXPR   // ==, !=, >, <, >=, <=
} ASTNodeType;
```

#### 2️⃣ ASTNode - Nœud de l'AST

```c
typedef struct ASTNode {
    ASTNodeType type;              // Type du nœud
    char* valeur;                  // Valeur (nom variable, opérateur)
    int nombre;                    // Valeur numérique
    struct ASTNode** enfants;      // Tableau d'enfants
    int nb_enfants;                // Nombre d'enfants
    int capacite;                  // Capacité du tableau
    struct ASTNode* condition;     // Condition (pour si/tantque)
    struct ASTNode* bloc_si;       // Bloc si vrai
    struct ASTNode* bloc_sinon;    // Bloc si faux
} ASTNode;
```

**Représentation visuelle d'un nœud :**

```
┌──────────────────────────────────────┐
│ ASTNode                              │
├──────────────────────────────────────┤
│ type:      AST_AFFECTATION           │
│ valeur:    "x"                       │
│ enfants[]: [NOMBRE(5)]               │
│ nb_enfants: 1                        │
└──────────────────────────────────────┘
```

### 📖 Grammaire du Langage

#### Notation EBNF

```ebnf
programme        ::= { instruction }

instruction      ::= affectation 
                   | affichage 
                   | condition 
                   | boucle

affectation      ::= "variable" IDENTIFICATEUR ["=" expression] ";"
                   | IDENTIFICATEUR "=" expression ";"

affichage        ::= "afficher" "(" expression ")" ";"

condition        ::= "si" "(" condition_expr ")" bloc 
                     ["sinon" bloc]

boucle           ::= "tantque" "(" condition_expr ")" bloc

bloc             ::= "{" { instruction } "}"

condition_expr   ::= expression operateur_comp expression

expression       ::= terme { ("+" | "-") terme }

terme            ::= facteur { ("*" | "/" | "%") facteur }

facteur          ::= NOMBRE 
                   | IDENTIFICATEUR 
                   | "(" expression ")"

operateur_comp   ::= "==" | "!=" | ">" | "<" | ">=" | "<="
```

### 🎨 Exemple d'AST

**Code :**
```galant
variable x = 5;
si (x > 0) {
  afficher(x);
}
```

**AST Textuel :**
```
PROGRAMME
├── AFFECTATION [x]
│   └── NOMBRE [5] (5)
└── CONDITION
    ├── CONDITION_EXPR [>]
    │   ├── VARIABLE [x]
    │   └── NOMBRE [0] (0)
    └── BLOC
        └── AFFICHAGE
            └── VARIABLE [x]
```

**AST Visuel :**

```mermaid
graph TD
    A[PROGRAMME] --> B[AFFECTATION x]
    A --> C[CONDITION]
    
    B --> B1[NOMBRE 5]
    
    C --> C1[CONDITION_EXPR >]
    C --> C2[BLOC SI]
    
    C1 --> C1A[VARIABLE x]
    C1 --> C1B[NOMBRE 0]
    
    C2 --> C2A[AFFICHAGE]
    C2A --> C2A1[VARIABLE x]
    
    style A fill:#e3f2fd,stroke:#1976d2,stroke-width:2px
    style B fill:#fff3e0,stroke:#f57c00,stroke-width:2px
    style C fill:#f3e5f5,stroke:#7b1fa2,stroke-width:2px
    style B1 fill:#c8e6c9,stroke:#388e3c
    style C1 fill:#ffe0b2,stroke:#e64a19
    style C2 fill:#f8bbd0,stroke:#c2185b
```

### ⚙️ Algorithme de Parsing

#### Descente Récursive

```mermaid
graph TD
    A[parser_analyser] --> B[parser_instruction]
    B --> C{Type?}
    
    C -->|variable| D[parser_affectation]
    C -->|afficher| E[parser_affichage]
    C -->|si| F[parser_condition]
    C -->|tantque| G[parser_boucle]
    
    D --> H[parser_expression]
    E --> H
    F --> I[parser_condition]
    G --> I
    
    H --> J[parser_terme]
    J --> K[parser_facteur]
    
    style A fill:#4caf50,color:#fff
    style B fill:#2196f3,color:#fff
    style H fill:#ff9800,color:#fff
    style J fill:#e91e63,color:#fff
    style K fill:#9c27b0,color:#fff
```

---

## ✅ Phase 3 : Analyse Sémantique

### 🎯 Objectif

> Vérifier la **cohérence sémantique** et **exécuter** le programme

### 📁 Fichiers

| Fichier | Rôle |
|---------|------|
| `semantic.c` | 🔧 Implémentation |
| `semantic.h` | 📋 Interface et structures |

### 🏗️ Structures de Données

#### 1️⃣ Variable

```c
typedef struct {
    char* nom;          // Nom de la variable
    int valeur;         // Valeur actuelle
    int initialise;     // 0 = non initialisée, 1 = initialisée
} Variable;
```

**États d'une variable :**

```mermaid
stateDiagram-v2
    [*] --> Déclarée: variable x;
    Déclarée --> Initialisée: x = 5;
    Initialisée --> Modifiée: x = 10;
    Modifiée --> Initialisée: x = x + 1;
    
    Déclarée --> Erreur: afficher(x)
    
    note right of Erreur
        Variable utilisée
        avant initialisation
    end note
```

#### 2️⃣ Environnement

```c
#define MAX_VARIABLES 1000

typedef struct {
    Variable variables[MAX_VARIABLES];  // Tableau de variables
    int nb_variables;                   // Nombre de variables
} Environnement;
```

### ⚙️ Fonctions Principales

#### 🔍 Recherche de Variable

```c
Variable* semantic_trouver_variable(Environnement* env, const char* nom)
```

**Algorithme :**
```
POUR chaque variable dans l'environnement :
    SI variable.nom == nom :
        RETOURNER pointeur vers variable
RETOURNER NULL
```

**Complexité :** `O(n)` où n = nombre de variables

**Optimisation possible :** Table de hachage → `O(1)`

#### 📝 Définition de Variable

```c
void semantic_definir_variable(Environnement* env, const char* nom, int valeur)
```

**Flux d'exécution :**

```mermaid
graph TD
    A[Définir variable] --> B{Variable existe?}
    B -->|Oui| C[Modifier valeur]
    B -->|Non| D[Créer nouvelle variable]
    
    C --> E[Marquer comme initialisée]
    D --> F[Ajouter à l'environnement]
    F --> E
    E --> G[Fin]
    
    style A fill:#2196f3,color:#fff
    style C fill:#4caf50,color:#fff
    style D fill:#ff9800,color:#fff
    style G fill:#4caf50,color:#fff
```

### 🔄 Évaluation d'Expressions

#### Algorithme Récursif

```c
static int evaluer_expression(Environnement* env, ASTNode* node)
```

**Arbre de décision :**

```mermaid
graph TD
    A[evaluer_expression] --> B{Type de nœud?}
    
    B -->|NOMBRE| C[Retourner valeur]
    B -->|VARIABLE| D[Chercher dans env]
    B -->|OPERATEUR| E[Évaluer récursivement]
    B -->|CONDITION_EXPR| F[Évaluer comparaison]
    
    D --> D1{Variable existe?}
    D1 -->|Non| D2[ERREUR: Non déclarée]
    D1 -->|Oui| D3{Initialisée?}
    D3 -->|Non| D4[ERREUR: Non initialisée]
    D3 -->|Oui| D5[Retourner valeur]
    
    E --> E1[Évaluer gauche]
    E --> E2[Évaluer droite]
    E1 --> E3[Appliquer opérateur]
    E2 --> E3
    
    style A fill:#2196f3,color:#fff
    style C fill:#4caf50,color:#fff
    style D2 fill:#f44336,color:#fff
    style D4 fill:#f44336,color:#fff
    style D5 fill:#4caf50,color:#fff
```

### 🎯 Vérifications Sémantiques

<table>
<tr>
<th>🔍 Vérification</th>
<th>📝 Description</th>
<th>❌ Erreur</th>
</tr>
<tr>
<td><b>Variable Déclarée</b></td>
<td>La variable existe dans l'environnement</td>
<td>

```
variable 'x' non declaree
```

</td>
</tr>
<tr>
<td><b>Variable Initialisée</b></td>
<td>La variable a une valeur assignée</td>
<td>

```
variable 'x' utilisee 
avant initialisation
```

</td>
</tr>
<tr>
<td><b>Division par Zéro</b></td>
<td>Le diviseur n'est pas nul</td>
<td>

```
division par zero
```

</td>
</tr>
<tr>
<td><b>Modulo par Zéro</b></td>
<td>Le modulo n'est pas nul</td>
<td>

```
modulo par zero
```

</td>
</tr>
</table>

---

## 🎯 Module Principal

### 📁 Fichier

- `main.c` - Point d'entrée du compilateur

### 🔄 Flux d'Exécution

```mermaid
graph TD
    A[main] --> B[Vérifier arguments]
    B --> C[Lire fichier]
    C --> D[Afficher source]
    D --> E["🔍 Phase 1: Lexer"]
    E --> F["🌳 Phase 2: Parser"]
    F --> G["✅ Phase 3: Semantic"]
    G --> H[Libérer mémoire]
    H --> I[Fin]
    
    B -.->|Erreur| J[Usage]
    C -.->|Erreur| K[Fichier non trouvé]
    E -.->|Erreur| L[Erreur lexicale]
    F -.->|Erreur| M[Erreur syntaxique]
    G -.->|Erreur| N[Erreur sémantique]
    
    style A fill:#4caf50,color:#fff
    style E fill:#fff3e0,stroke:#f57c00,stroke-width:2px
    style F fill:#f3e5f5,stroke:#7b1fa2,stroke-width:2px
    style G fill:#e8f5e9,stroke:#388e3c,stroke-width:2px
    style I fill:#4caf50,color:#fff
    
    style J fill:#f44336,color:#fff
    style K fill:#f44336,color:#fff
    style L fill:#f44336,color:#fff
    style M fill:#f44336,color:#fff
    style N fill:#f44336,color:#fff
```

### 📝 Code Principal

```c
int main(int argc, char* argv[]) {
    // 1. Vérification des arguments
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier.gal>\n", argv[0]);
        return 1;
    }

    // 2. Lecture du fichier
    char* source = lire_fichier(argv[1]);

    // 3. Affichage du code source
    printf("=== Code Source ===\n%s\n", source);

    // 4. Phase Lexicale
    Lexer* lexer = lexer_creer(source);
    lexer_analyser(lexer);
    lexer_afficher_tokens(lexer);

    // 5. Phase Syntaxique
    Parser* parser = parser_creer(lexer);
    ASTNode* ast = parser_analyser(parser);
    parser_afficher_ast(ast, 0);

    // 6. Phase Sémantique
    Environnement* env = semantic_creer_env();
    semantic_executer(env, ast);

    // 7. Libération mémoire
    semantic_liberer_env(env);
    parser_liberer_ast(ast);
    parser_liberer(parser);
    lexer_liberer(lexer);
    free(source);
    
    return 0;
}
```

---

## 💾 Gestion Mémoire

### 🎯 Stratégie Générale

```mermaid
graph LR
    A[Allocation<br/>dynamique] --> B[Utilisation]
    B --> C[Expansion<br/>si nécessaire]
    C --> D[Libération<br/>explicite]
    
    style A fill:#4caf50,color:#fff
    style B fill:#2196f3,color:#fff
    style C fill:#ff9800,color:#fff
    style D fill:#f44336,color:#fff
```

### 📊 Par Module

#### 🔍 Lexer

```c
// ✅ Allocation
lexer->tokens = malloc(100 * sizeof(Token));

// 📈 Expansion (doublement de capacité)
if (lexer->nb_tokens >= lexer->capacite) {
    lexer->capacite *= 2;
    lexer->tokens = realloc(lexer->tokens, 
                           lexer->capacite * sizeof(Token));
}

// 🧹 Libération
for (int i = 0; i < lexer->nb_tokens; i++) {
    free(lexer->tokens[i].valeur);
}
free(lexer->tokens);
free(lexer);
```

**Croissance de la capacité :**

```
Capacité initiale: 100
Token 100: ×2 → 200
Token 200: ×2 → 400
Token 400: ×2 → 800
...
```

#### 🌳 Parser

```c
// ✅ Allocation des enfants
node->enfants = malloc(10 * sizeof(ASTNode*));

// 📈 Expansion
if (node->nb_enfants >= node->capacite) {
    node->capacite *= 2;
    node->enfants = realloc(node->enfants, 
                           node->capacite * sizeof(ASTNode*));
}

// 🧹 Libération (récursive)
void parser_liberer_ast(ASTNode* node) {
    if (!node) return;
    
    // Libérer récursivement les enfants
    for (int i = 0; i < node->nb_enfants; i++) {
        parser_liberer_ast(node->enfants[i]);
    }
    
    // Libérer les nœuds spéciaux
    if (node->condition) parser_liberer_ast(node->condition);
    if (node->bloc_si) parser_liberer_ast(node->bloc_si);
    if (node->bloc_sinon) parser_liberer_ast(node->bloc_sinon);
    
    // Libérer le nœud lui-même
    free(node->valeur);
    free(node->enfants);
    free(node);
}
```

#### ✅ Semantic

```c
// ✅ Environnement : tableau fixe
Variable variables[MAX_VARIABLES];

// 🧹 Libération
for (int i = 0; i < env->nb_variables; i++) {
    free(env->variables[i].nom);
}
free(env);
```

### ⚠️ Prévention des Fuites Mémoire

<table>
<tr>
<th>✅ Bonne Pratique</th>
<th>📝 Description</th>
</tr>
<tr>
<td><b>Ordre de libération</b></td>
<td>Libérer les enfants avant les parents (récursif)</td>
</tr>
<tr>
<td><b>Vérification NULL</b></td>
<td>Toujours vérifier avant <code>free()</code></td>
</tr>
<tr>
<td><b>Pas de double free</b></td>
<td>Ne jamais libérer deux fois la même mémoire</td>
</tr>
<tr>
<td><b>Libération complète</b></td>
<td>Libérer tous les pointeurs alloués</td>
</tr>
</table>

---

## 🐛 Gestion des Erreurs

### 📊 Types d'Erreurs

```mermaid
graph TD
    A[Erreurs] --> B[Lexicales]
    A --> C[Syntaxiques]
    A --> D[Sémantiques]
    
    B --> B1[Caractère invalide]
    B --> B2[Token malformé]
    
    C --> C1[Syntaxe incorrecte]
    C --> C2[Parenthèses non fermées]
    C --> C3[Point-virgule manquant]
    
    D --> D1[Variable non déclarée]
    D --> D2[Variable non initialisée]
    D --> D3[Division par zéro]
    
    style A fill:#1976d2,color:#fff
    style B fill:#ff9800,color:#fff
    style C fill:#f44336,color:#fff
    style D fill:#e91e63,color:#fff
```

### 🔧 Mécanisme d'Erreur

#### Flag Global

```c
static int error_flag = 0;  // Variable globale statique
```

**États du flag :**

```mermaid
stateDiagram-v2
    [*] --> Normal: Initialisation
    Normal --> Erreur: Erreur détectée
    Erreur --> [*]: Fin d'exécution
    
    note right of Normal
        error_flag = 0
        Exécution continue
    end note
    
    note right of Erreur
        error_flag = 1
        Exécution arrêtée
    end note
```

#### Propagation des Erreurs

```c
// ✅ Définir l'erreur
if (condition_erreur) {
    fprintf(stderr, "Erreur: %s\n", message);
    error_flag = 1;
    return;
}

// ✅ Vérifier l'erreur
if (error_flag) return;  // Arrêter l'exécution
```

### 📝 Messages d'Erreur

<table>
<tr>
<th>Type</th>
<th>Message</th>
<th>Action</th>
</tr>
<tr>
<td>🔍 Lexicale</td>
<td><code>Caractère invalide '@' à la ligne 5</code></td>
<td>Corriger le caractère</td>
</tr>
<tr>
<td>🌳 Syntaxique</td>
<td><code>Erreur syntaxique à la ligne 10<br/>Point-virgule attendu</code></td>
<td>Ajouter <code>;</code></td>
</tr>
<tr>
<td>✅ Sémantique</td>
<td><code>Erreur semantique:<br/>variable 'x' non declaree</code></td>
<td>Déclarer la variable</td>
</tr>
</table>

---

## 📊 Complexité et Performance

### 🎯 Analyse de Complexité

| Phase | ⏱️ Temporelle | 💾 Spatiale | 📝 Détails |
|-------|--------------|------------|----------|
| **🔍 Lexer** | `O(n)` | `O(n)` | n = longueur du code |
| **🌳 Parser** | `O(m)` | `O(m)` | m = nombre de tokens |
| **✅ Semantic** | `O(i × d)` | `O(v)` | i = itérations, d = profondeur AST, v = variables |

### 📈 Graphique de Performance

```
Temps d'exécution (ms)
│
│     ╱
│    ╱ Semantic (O(i×d))
│   ╱
│  ╱  Parser (O(m))
│ ╱
│╱ Lexer (O(n))
└──────────────────── Taille du programme
```

### 🚀 Optimisations Possibles

<table>
<tr>
<th>🎯 Optimisation</th>
<th>📊 Gain</th>
<th>💡 Description</th>
</tr>
<tr>
<td><b>Table de hachage</b></td>
<td><code>O(1)</code> au lieu de <code>O(n)</code></td>
<td>Pour la recherche de variables</td>
</tr>
<tr>
<td><b>Pool de mémoire</b></td>
<td>Allocation plus rapide</td>
<td>Pour les nœuds AST</td>
</tr>
<tr>
<td><b>Compilation JIT</b></td>
<td>Exécution plus rapide</td>
<td>Compiler en code machine</td>
</tr>
<tr>
<td><b>Cache d'expressions</b></td>
<td>Éviter recalculs</td>
<td>Pour expressions constantes</td>
</tr>
</table>

### ⚠️ Limitations Actuelles

```
┌─────────────────────────────────────────┐
│ MAX_VARIABLES = 1000                    │
│ → Tableau fixe, pas dynamique           │
├─────────────────────────────────────────┤
│ Recherche linéaire O(n)                 │
│ → Pas de table de hachage               │
├─────────────────────────────────────────┤
│ Pas d'optimisation de l'AST             │
│ → Expressions non simplifiées           │
├─────────────────────────────────────────┤
│ Interprétation pure                     │
│ → Pas de compilation vers code machine  │
└─────────────────────────────────────────┘
```

---

## 🛠️ Technologies Utilisées

<table>
<tr>
<td align="center">

### 📝 Langage
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)

C99 Standard

</td>
<td align="center">

### 🔨 Compilateur
![GCC](https://img.shields.io/badge/GCC-4.8+-orange?style=for-the-badge)

GNU Compiler Collection

</td>
<td align="center">

### ⚙️ Build System
![Make](https://img.shields.io/badge/Make-GNU-red?style=for-the-badge)

GNU Make

</td>
</tr>
</table>

**Plateformes supportées :**
- 🐧 Linux
- 🪟 Windows (via MinGW/WSL)
- 🍎 macOS

---

## 🎨 Diagrammes de Flux

### 🔄 Cycle de Vie Complet

```mermaid
sequenceDiagram
    participant U as Utilisateur
    participant M as main.c
    participant L as Lexer
    participant P as Parser
    participant S as Semantic
    
    U->>M: ./galant-compiler prog.gal
    M->>M: Lire fichier
    M->>L: lexer_creer(source)
    L-->>M: Lexer*
    M->>L: lexer_analyser()
    L->>L: Tokenization
    L-->>M: Tokens[]
    
    M->>P: parser_creer(lexer)
    P-->>M: Parser*
    M->>P: parser_analyser()
    P->>P: Construire AST
    P-->>M: ASTNode*
    
    M->>S: semantic_creer_env()
    S-->>M: Environnement*
    M->>S: semantic_executer(env, ast)
    S->>S: Exécuter programme
    S-->>M: Résultat
    
    M->>M: Libérer mémoire
    M-->>U: Sortie finale
```

---

## 📚 Ressources

| 📄 Document | 📝 Description |
|------------|---------------|
| [README.md](README.md) | Vue d'ensemble du projet |
| [GUIDE_UTILISATION.md](GUIDE_UTILISATION.md) | Guide utilisateur complet |
| [LICENSE](LICENSE) | Licence MIT |

---

## 🎯 Conclusion

L'architecture de GALANT suit les **principes classiques** de construction de compilateur tout en restant **simple et éducative**. Chaque phase est clairement séparée, facilitant la compréhension et la maintenance.

### 🌟 Points Forts

- ✅ **Modularité** - Séparation claire des responsabilités
- ✅ **Clarté** - Code lisible et bien documenté
- ✅ **Robustesse** - Gestion complète des erreurs
- ✅ **Éducatif** - Idéal pour l'apprentissage

### 🚀 Extensions Possibles

- 📝 Fonctions définies par l'utilisateur
- 📚 Tableaux et structures de données
- 🔗 Opérateurs logiques (ET, OU, NON)
- 💾 Génération de code assembleur
- 🐛 Débogueur intégré

---

<div align="center">

**Documentation technique complète pour GALANT** 🧠

[![Retour au README](https://img.shields.io/badge/←_Retour_au-README-blue?style=for-the-badge)](README.md)
[![Guide](https://img.shields.io/badge/Guide-Utilisation-green?style=for-the-badge)](GUIDE_UTILISATION.md)

---

*Fait avec ❤️ pour l'éducation en français* 🇫🇷

</div>
