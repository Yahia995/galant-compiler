#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

// Types de tokens
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

// Mots-clés du langage GALANT
typedef enum {
    KW_VARIABLE,
    KW_AFFICHER,
    KW_SI,
    KW_SINON,
    KW_TANTQUE,
    KW_NONE
} MotCle;

// Structure pour un token
typedef struct {
    TokenType type;
    char* valeur;
    int ligne;
    int colonne;
    MotCle mot_cle;
    int valeur_nombre;
} Token;

// Structure du lexer
typedef struct {
    const char* source;
    size_t pos;
    int ligne;
    int colonne;
    Token* tokens;
    int nb_tokens;
    int capacite;
} Lexer;

// Fonctions publiques du lexer
Lexer* lexer_creer(const char* source);
void lexer_analyser(Lexer* lexer);
void lexer_afficher_tokens(Lexer* lexer);
void lexer_liberer(Lexer* lexer);

#endif