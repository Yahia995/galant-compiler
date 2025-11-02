#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Types d'nœuds AST
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

// Structure pour nœud AST
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

// Structure du parser
typedef struct {
    Lexer* lexer;
    int pos;
} Parser;

Parser* parser_creer(Lexer* lexer);
ASTNode* parser_analyser(Parser* parser);
void parser_afficher_ast(ASTNode* node, int profondeur);
void parser_liberer_ast(ASTNode* node);
void parser_liberer(Parser* parser);

#endif
