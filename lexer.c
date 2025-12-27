#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char lexer_peek(Lexer* lexer) {
    if ((size_t)lexer->pos >= strlen(lexer->source)) {
        return '\0';
    }
    return lexer->source[lexer->pos];
}

static char lexer_peek_next(Lexer* lexer) {
    if ((size_t)lexer->pos + 1 >= strlen(lexer->source)) {
        return '\0';
    }
    return lexer->source[lexer->pos + 1];
}

static void lexer_ajouter_token(Lexer* lexer, Token token) {
    if (lexer->nb_tokens >= lexer->capacite) {
        lexer->capacite *= 2;
        lexer->tokens = realloc(lexer->tokens, lexer->capacite * sizeof(Token));
    }
    lexer->tokens[lexer->nb_tokens++] = token;
}

static MotCle lexer_est_mot_cle(const char* str) {
    if (strcmp(str, "variable") == 0) return KW_VARIABLE;
    if (strcmp(str, "afficher") == 0) return KW_AFFICHER;
    if (strcmp(str, "si") == 0) return KW_SI;
    if (strcmp(str, "sinon") == 0) return KW_SINON;
    if (strcmp(str, "tantque") == 0) return KW_TANTQUE;
    return KW_NONE;
}

static void lexer_lire_nombre(Lexer* lexer, Token* token) {
    char buffer[256] = {0};
    int idx = 0;
    
    while (idx < 255 && isdigit(lexer_peek(lexer))) {
        buffer[idx++] = lexer->source[lexer->pos++];
        lexer->colonne++;
    }
    buffer[idx] = '\0';
    
    token->type = TOKEN_NOMBRE;
    token->valeur = malloc(strlen(buffer) + 1);
    strcpy(token->valeur, buffer);
    token->valeur_nombre = atoi(buffer);
}

static void lexer_lire_identificateur(Lexer* lexer, Token* token) {
    char buffer[256] = {0};
    int idx = 0;
    
    while (idx < 255 && (isalnum(lexer_peek(lexer)) || lexer_peek(lexer) == '_')) {
        buffer[idx++] = lexer->source[lexer->pos++];
        lexer->colonne++;
    }
    buffer[idx] = '\0';
    
    MotCle mc = lexer_est_mot_cle(buffer);
    if (mc != KW_NONE) {
        token->type = TOKEN_MOT_CLE;
        token->mot_cle = mc;
    } else {
        token->type = TOKEN_IDENTIFICATEUR;
    }
    
    token->valeur = malloc(strlen(buffer) + 1);
    strcpy(token->valeur, buffer);
}

static void lexer_lire_operateur(Lexer* lexer, Token* token) {
    char c = lexer_peek(lexer);
    char next = lexer_peek_next(lexer);
    
    token->valeur = malloc(3);
    
    if ((c == '=' && next == '=') || (c == '!' && next == '=') ||
        (c == '>' && next == '=') || (c == '<' && next == '=')) {
        token->type = TOKEN_OPERATEUR_COMP;
        token->valeur[0] = c;
        token->valeur[1] = next;
        token->valeur[2] = '\0';
        lexer->pos += 2;
        lexer->colonne += 2;
    } else if (c == '>' || c == '<') {
        token->type = TOKEN_OPERATEUR_COMP;
        token->valeur[0] = c;
        token->valeur[1] = '\0';
        lexer->pos++;
        lexer->colonne++;
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        token->type = TOKEN_OPERATEUR_ARITH;
        token->valeur[0] = c;
        token->valeur[1] = '\0';
        lexer->pos++;
        lexer->colonne++;
    }
    else if (c == '=') {
        token->type = TOKEN_PONCTUATION;
        token->valeur[0] = '=';
        token->valeur[1] = '\0';
        lexer->pos++;
        lexer->colonne++;
    }
}

Lexer* lexer_creer(const char* source) {
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->source = source;
    lexer->pos = 0;
    lexer->ligne = 1;
    lexer->colonne = 1;
    lexer->tokens = malloc(100 * sizeof(Token));
    lexer->nb_tokens = 0;
    lexer->capacite = 100;
    return lexer;
}

void lexer_analyser(Lexer* lexer) {
    while ((size_t)lexer->pos < strlen(lexer->source)) {
        char c = lexer_peek(lexer);
        
        // Ignorer les espaces et retours à la ligne
        if (c == ' ' || c == '\t') {
            lexer->pos++;
            lexer->colonne++;
            continue;
        }
        
        if (c == '\n') {
            lexer->pos++;
            lexer->ligne++;
            lexer->colonne = 1;
            continue;
        }
        
        // Ignorer les commentaires
        if (c == '#') {
            while (lexer_peek(lexer) != '\n' && lexer_peek(lexer) != '\0') {
                lexer->pos++;
            }
            continue;
        }
        
        Token token = {0};
        token.ligne = lexer->ligne;
        token.colonne = lexer->colonne;
        
        if (isdigit(c)) {
            lexer_lire_nombre(lexer, &token);
        } else if (isalpha(c) || c == '_') {
            lexer_lire_identificateur(lexer, &token);
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
                   c == '=' || c == '!' || c == '>' || c == '<') {
            lexer_lire_operateur(lexer, &token);
        } else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';') {
            token.type = TOKEN_PONCTUATION;
            token.valeur = malloc(2);
            token.valeur[0] = c;
            token.valeur[1] = '\0';
            lexer->pos++;
            lexer->colonne++;
        } else {
            token.type = TOKEN_ERREUR;
            token.valeur = malloc(2);
            token.valeur[0] = c;
            token.valeur[1] = '\0';
            lexer->pos++;
            lexer->colonne++;
        }
        
        lexer_ajouter_token(lexer, token);
    }
    
    // Ajouter token EOF
    Token eof = {0};
    eof.type = TOKEN_EOF;
    eof.valeur = malloc(1);
    eof.valeur[0] = '\0';
    lexer_ajouter_token(lexer, eof);
}

void lexer_afficher_tokens(Lexer* lexer) {
    printf("\n=== Analyse Lexicale ===\n");
    printf("[v0] Nombre de tokens: %d\n", lexer->nb_tokens);
    fflush(stdout);
    
    const char* type_names[] = {
        "NOMBRE", "IDENTIFICATEUR", "MOT_CLE", "OP_ARITH",
        "OP_COMP", "PONCTUATION", "EOF", "ERREUR"
    };
    const char* kw_names[] = {
        "VARIABLE", "AFFICHER", "SI", "SINON", "TANTQUE", "AUCUN"
    };
    
    for (int i = 0; i < lexer->nb_tokens; i++) {
        Token t = lexer->tokens[i];
        printf("[%3d] %-15s = '%s'", i, type_names[t.type], t.valeur);
        if (t.type == TOKEN_NOMBRE) {
            printf(" (valeur: %d)", t.valeur_nombre);
        } else if (t.type == TOKEN_MOT_CLE) {
            printf(" (mot-cle: %s)", kw_names[t.mot_cle]);
        }
        printf("\n");
        fflush(stdout);
    }
}

void lexer_liberer(Lexer* lexer) {
    for (int i = 0; i < lexer->nb_tokens; i++) {
        free(lexer->tokens[i].valeur);
    }
    free(lexer->tokens);
    free(lexer);
}
