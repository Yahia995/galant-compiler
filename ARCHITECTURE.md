# 🧠 Architecture du Compilateur **GALANT**

> Un compilateur éducatif complet pour un langage de programmation **entièrement en français**.  
> Il suit une architecture classique en **trois phases** : *analyse lexicale*, *syntaxique* et *sémantique*.

---

## 🧩 Vue d’ensemble

```text
Code Source (.gal)
        |
        v
    [LEXER]          --> Analyse Lexicale
        |
        v (Tokens)
    [PARSER]         --> Analyse Syntaxique
        |
        v (AST)
    [SEMANTIC]       --> Analyse Sémantique + Exécution
        |
        v
    Résultat
⚙️ 1. Phase Lexicale (lexer.c / lexer.h)
🎯 Objectif
Décomposer le code source en jetons élémentaires (tokens).

🧱 Structures de Données
c
Copy code
typedef enum {
    TOKEN_NOMBRE,
    TOKEN_IDENTIFICATEUR,
    TOKEN_MOT_CLE,
    TOKEN_OPERATEUR_ARITH,
    TOKEN_OPERATEUR_COMP,
    TOKEN_PONCTUATION,
    TOKEN_EOF,
    TOKEN_ERREUR
} TokenType;

typedef struct {
    TokenType type;
    char* valeur;
    int ligne;
    int colonne;
    MotCle mot_cle;
    int valeur_nombre;
} Token;

typedef struct {
    const char* source;
    size_t pos;
    int ligne;
    int colonne;
    Token* tokens;
    int nb_tokens;
    int capacite;
} Lexer;
🧠 Méthodes Principales
Fonction	Description
lexer_creer(const char* source)	Alloue et initialise le lexer
lexer_analyser(Lexer* lexer)	Parcourt le code et génère les tokens
lexer_afficher_tokens(Lexer* lexer)	Affiche chaque token avec son type et position

Algorithme principal :

TANT QUE pas fin du fichier :
  1. Ignorer espaces et commentaires (#)
  2. Si chiffre -> lire_nombre()
  3. Si lettre -> lire_identificateur() ou lire_mot_cle()
  4. Si opérateur -> lire_operateur()
  5. Si ponctuation -> ajouter token
🧩 Exemple

variable x = 5;
Tokens générés :

[0] MOT_CLE         = 'variable'
[1] IDENTIFICATEUR  = 'x'
[2] PONCTUATION     = '='
[3] NOMBRE          = '5'
[4] PONCTUATION     = ';'
🧮 2. Phase Syntaxique (parser.c / parser.h)
🎯 Objectif
Vérifie la grammaire et construit l’Arbre de Syntaxe Abstraite (AST).

🧱 Structures de Données

typedef enum {
    AST_PROGRAMME,
    AST_AFFECTATION,
    AST_AFFICHAGE,
    AST_CONDITION,
    AST_BOUCLE,
    AST_BLOC,
    AST_EXPRESSION,
    AST_NOMBRE,
    AST_VARIABLE,
    AST_OPERATEUR,
    AST_CONDITION_EXPR
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char* valeur;
    int nombre;
    struct ASTNode** enfants;
    int nb_enfants;
    int capacite;
    struct ASTNode* condition;
    struct ASTNode* bloc_si;
    struct ASTNode* bloc_sinon;
} ASTNode;

typedef struct {
    Lexer* lexer;
    int pos;
} Parser;
📜 Grammaire EBNF supportée

programme        ::= { instruction }
instruction      ::= affectation | affichage | condition | boucle
affectation      ::= "variable" IDENTIFICATEUR "=" expression ";"
affichage        ::= "afficher" "(" expression ")"
condition        ::= "si" "(" condition_expr ")" bloc ["sinon" bloc]
boucle           ::= "tantque" "(" condition_expr ")" bloc
bloc             ::= "{" { instruction } "}"
expression       ::= terme { ('+' | '-') terme }
terme            ::= facteur { ('*' | '/' | '%') facteur }
facteur          ::= NOMBRE | IDENTIFICATEUR | "(" expression ")"

⚙️ Méthodes Principales
Fonction	Description
parser_creer(Lexer* lexer)	Initialise le parser
parser_analyser(Parser* parser)	Construit l’AST complet
parser_afficher_ast(ASTNode* node, int profondeur)	Affiche l’AST hiérarchiquement

Algorithme simplifié :

POUR CHAQUE token :
  - Identifier le type d’instruction
  - Construire le nœud AST correspondant
  - Ajouter au programme
🌳 Exemple d’AST

variable x = 5;
afficher(x);
AST :

PROGRAMME
  ├── AFFECTATION : x = 5
  └── AFFICHAGE   : x
🔍 3. Phase Sémantique (semantic.c / semantic.h)
🎯 Objectif
Vérifie la cohérence sémantique et exécute le programme.

🧱 Structures de Données

typedef struct {
    char* nom;
    int valeur;
    int initialise;
} Variable;

typedef struct {
    Variable variables[MAX_VARIABLES];
    int nb_variables;
} Environnement;

⚙️ Méthodes Principales
Fonction	Rôle
semantic_creer_env()	Initialise l’environnement
semantic_definir_variable()	Crée ou met à jour une variable
semantic_trouver_variable()	Recherche une variable
semantic_evaluer()	Évalue une expression
semantic_executer()	Exécute le programme à partir de l’AST

🧠 Exemple d’exécution

variable n = 5;
variable resultat = 1;
tantque (i <= n) {
  resultat = resultat * i;
  i = i + 1;
}
afficher(resultat);
Sortie :
120

🏗️ 4. Flux Complet (main.c)
🔄 Étapes Principales
Lire le fichier .gal

Analyse lexicale → tokens

Analyse syntaxique → AST

Analyse sémantique → exécution

Libération mémoire

🧰 Pseudocode

main(argc, argv) {
  source = lire_fichier(argv[1]);
  lexer = lexer_creer(source);
  lexer_analyser(lexer);
  parser = parser_creer(lexer);
  ast = parser_analyser(parser);
  env = semantic_creer_env();
  semantic_executer(env, ast);
  cleanup(...);
}

💾 Gestion Mémoire
Module	Stratégie
Lexer	Tokens dynamiques, doublement de capacité
Parser	Enfants AST dynamiques
Semantic	Variables avec malloc, tableau fixe (MAX_VARIABLES = 1000)

⚠️ Gestion des Erreurs
Étape	Vérifications
Lexer	Caractères non reconnus
Parser	Erreurs de grammaire
Semantic	Variables non déclarées, division par zéro

🔢 Opérateurs Supportés
Type	Opérateurs	Précédence
Arithmétiques	*, /, %, +, -	Haute → Basse
Comparaisons	==, !=, >, <, >=, <=	—
Assignation	=	—

⏱️ Complexité
Étape	Complexité
Analyse lexicale	O(n)
Analyse syntaxique	O(m)
Évaluation expression	O(profondeur AST)
Exécution programme	O(itérations)

🧰 Technologies Utilisées
Langage : C

Build : Makefile

Outils : GCC, Linux CLI

Architecture : Modulaire (Lexer, Parser, Semantic)