#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ASTNode* parser_creer_noeud(ASTNodeType type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = type;
    node->valeur = NULL;
    node->nombre = 0;
    node->enfants = malloc(10 * sizeof(ASTNode*));
    node->nb_enfants = 0;
    node->capacite = 10;
    node->condition = NULL;
    node->bloc_si = NULL;
    node->bloc_sinon = NULL;
    return node;
}

static void parser_ajouter_enfant(ASTNode* parent, ASTNode* enfant) {
    if (parent->nb_enfants >= parent->capacite) {
        parent->capacite *= 2;
        parent->enfants = realloc(parent->enfants, parent->capacite * sizeof(ASTNode*));
    }
    parent->enfants[parent->nb_enfants++] = enfant;
}

static Token parser_peek(Parser* parser) {
    return parser->lexer->tokens[parser->pos];
}

static Token parser_next(Parser* parser) {
    return parser->lexer->tokens[parser->pos++];
}

static ASTNode* parser_instruction(Parser* parser);

static ASTNode* parser_expression(Parser* parser);

static ASTNode* parser_facteur(Parser* parser) {
    Token t = parser_peek(parser);
    
    if (t.type == TOKEN_NOMBRE) {
        ASTNode* node = parser_creer_noeud(AST_NOMBRE);
        node->nombre = t.valeur_nombre;
        node->valeur = malloc(strlen(t.valeur) + 1);
        strcpy(node->valeur, t.valeur);
        parser_next(parser);
        return node;
    }
    
    if (t.type == TOKEN_IDENTIFICATEUR) {
        ASTNode* node = parser_creer_noeud(AST_VARIABLE);
        node->valeur = malloc(strlen(t.valeur) + 1);
        strcpy(node->valeur, t.valeur);
        parser_next(parser);
        return node;
    }
    
    if (t.type == TOKEN_PONCTUATION && strcmp(t.valeur, "(") == 0) {
        parser_next(parser);
        ASTNode* expr = parser_expression(parser);
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, ")") == 0) {
            parser_next(parser);
        }
        return expr;
    }
    
    return NULL;
}

static ASTNode* parser_terme(Parser* parser) {
    ASTNode* gauche = parser_facteur(parser);
    
    while (parser_peek(parser).type == TOKEN_OPERATEUR_ARITH) {
        Token op = parser_next(parser);
        ASTNode* droit = parser_facteur(parser);
        
        ASTNode* node = parser_creer_noeud(AST_OPERATEUR);
        node->valeur = malloc(strlen(op.valeur) + 1);
        strcpy(node->valeur, op.valeur);
        parser_ajouter_enfant(node, gauche);
        parser_ajouter_enfant(node, droit);
        gauche = node;
    }
    
    return gauche;
}

static ASTNode* parser_expression(Parser* parser) {
    ASTNode* gauche = parser_terme(parser);
    
    while (parser_peek(parser).type == TOKEN_OPERATEUR_ARITH &&
           (strcmp(parser_peek(parser).valeur, "+") == 0 || 
            strcmp(parser_peek(parser).valeur, "-") == 0)) {
        Token op = parser_next(parser);
        ASTNode* droit = parser_terme(parser);
        
        ASTNode* node = parser_creer_noeud(AST_OPERATEUR);
        node->valeur = malloc(strlen(op.valeur) + 1);
        strcpy(node->valeur, op.valeur);
        parser_ajouter_enfant(node, gauche);
        parser_ajouter_enfant(node, droit);
        gauche = node;
    }
    
    return gauche;
}

static ASTNode* parser_condition(Parser* parser) {
    ASTNode* gauche = parser_expression(parser);
    
    if (parser_peek(parser).type == TOKEN_OPERATEUR_COMP) {
        Token op = parser_next(parser);
        ASTNode* droit = parser_expression(parser);
        
        ASTNode* node = parser_creer_noeud(AST_CONDITION_EXPR);
        node->valeur = malloc(strlen(op.valeur) + 1);
        strcpy(node->valeur, op.valeur);
        parser_ajouter_enfant(node, gauche);
        parser_ajouter_enfant(node, droit);
        return node;
    }
    
    return gauche;
}

static ASTNode* parser_bloc(Parser* parser) {
    if (parser_peek(parser).type == TOKEN_PONCTUATION && 
        strcmp(parser_peek(parser).valeur, "{") == 0) {
        parser_next(parser);
    }
    ASTNode* bloc = parser_creer_noeud(AST_BLOC);
    
    while (parser_peek(parser).type != TOKEN_EOF) {
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, "}") == 0) {
            break;
        }
        ASTNode* instr = parser_instruction(parser);
        if (instr) parser_ajouter_enfant(bloc, instr);
    }
    
    if (parser_peek(parser).type == TOKEN_PONCTUATION && 
        strcmp(parser_peek(parser).valeur, "}") == 0) {
        parser_next(parser);
    }
    return bloc;
}

static ASTNode* parser_instruction(Parser* parser) {
    Token t = parser_peek(parser);
    
    if (t.type == TOKEN_MOT_CLE && t.mot_cle == KW_VARIABLE) {
        parser_next(parser);
        Token id = parser_next(parser);
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, "=") == 0) {
            parser_next(parser);
        }
        ASTNode* expr = parser_expression(parser);
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, ";") == 0) {
            parser_next(parser);
        }
        
        ASTNode* node = parser_creer_noeud(AST_AFFECTATION);
        node->valeur = malloc(strlen(id.valeur) + 1);
        strcpy(node->valeur, id.valeur);
        parser_ajouter_enfant(node, expr);
        return node;
    }
    
    if (t.type == TOKEN_IDENTIFICATEUR) {
        Token id = parser_next(parser);
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, "=") == 0) {
            parser_next(parser);
            ASTNode* expr = parser_expression(parser);
            if (parser_peek(parser).type == TOKEN_PONCTUATION && 
                strcmp(parser_peek(parser).valeur, ";") == 0) {
                parser_next(parser);
            }
            
            ASTNode* node = parser_creer_noeud(AST_AFFECTATION);
            node->valeur = malloc(strlen(id.valeur) + 1);
            strcpy(node->valeur, id.valeur);
            parser_ajouter_enfant(node, expr);
            return node;
        } else {
            // Not an assignment, rewind
            parser->pos--;
        }
    }
    
    if (t.type == TOKEN_MOT_CLE && t.mot_cle == KW_AFFICHER) {
        parser_next(parser);
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, "(") == 0) {
            parser_next(parser);
        }
        ASTNode* expr = parser_expression(parser);
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, ")") == 0) {
            parser_next(parser);
        }
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, ";") == 0) {
            parser_next(parser);
        }
        
        ASTNode* node = parser_creer_noeud(AST_AFFICHAGE);
        parser_ajouter_enfant(node, expr);
        return node;
    }
    
    if (t.type == TOKEN_MOT_CLE && t.mot_cle == KW_SI) {
        parser_next(parser);
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, "(") == 0) {
            parser_next(parser);
        }
        ASTNode* condition = parser_condition(parser);
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, ")") == 0) {
            parser_next(parser);
        }
        ASTNode* bloc = parser_bloc(parser);
        
        ASTNode* node = parser_creer_noeud(AST_CONDITION);
        node->condition = condition;
        node->bloc_si = bloc;
        
        if (parser_peek(parser).type == TOKEN_MOT_CLE && 
            parser_peek(parser).mot_cle == KW_SINON) {
            parser_next(parser);
            node->bloc_sinon = parser_bloc(parser);
        }
        return node;
    }
    
    if (t.type == TOKEN_MOT_CLE && t.mot_cle == KW_TANTQUE) {
        parser_next(parser);
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, "(") == 0) {
            parser_next(parser);
        }
        ASTNode* condition = parser_condition(parser);
        if (parser_peek(parser).type == TOKEN_PONCTUATION && 
            strcmp(parser_peek(parser).valeur, ")") == 0) {
            parser_next(parser);
        }
        ASTNode* bloc = parser_bloc(parser);
        
        ASTNode* node = parser_creer_noeud(AST_BOUCLE);
        node->condition = condition;
        node->bloc_si = bloc;
        return node;
    }
    
    if (t.type != TOKEN_EOF) {
        printf("[v0] Avertissement: token ignore a la position %d: %s\n", parser->pos, t.valeur);
        parser_next(parser);
    }
    
    return NULL;
}

Parser* parser_creer(Lexer* lexer) {
    Parser* parser = malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->pos = 0;
    return parser;
}

ASTNode* parser_analyser(Parser* parser) {
    printf("[v0] Debut de parser_analyser\n");
    fflush(stdout);
    ASTNode* programme = parser_creer_noeud(AST_PROGRAMME);
    
    int iterations = 0;
    while (parser_peek(parser).type != TOKEN_EOF) {
        iterations++;
        if (iterations > 1000) {
            printf("[v0] ERREUR: boucle infinie detectee dans parser_analyser (>1000 iterations)\n");
            fflush(stdout);
            break;
        }
        
        printf("[v0] Iteration %d, position: %d, type: %d\n", iterations, parser->pos, parser_peek(parser).type);
        fflush(stdout);
        
        ASTNode* instr = parser_instruction(parser);
        if (instr) {
            parser_ajouter_enfant(programme, instr);
        }
    }
    
    printf("[v0] Fin de parser_analyser - %d instructions parsees\n", programme->nb_enfants);
    fflush(stdout);
    
    return programme;
}

void parser_afficher_ast(ASTNode* node, int profondeur) {
    if (!node) return;
    
    const char* type_names[] = {
        "PROGRAMME", "AFFECTATION", "AFFICHAGE", "CONDITION", "BOUCLE",
        "BLOC", "EXPRESSION", "NOMBRE", "VARIABLE", "OPERATEUR", "CONDITION_EXPR"
    };
    
    for (int i = 0; i < profondeur; i++) printf("  ");
    printf("%s", type_names[node->type]);
    
    if (node->valeur) printf(" [%s]", node->valeur);
    if (node->type == AST_NOMBRE) printf(" (%d)", node->nombre);
    printf("\n");
    
    for (int i = 0; i < node->nb_enfants; i++) {
        parser_afficher_ast(node->enfants[i], profondeur + 1);
    }
}

void parser_liberer_ast(ASTNode* node) {
    if (!node) return;
    for (int i = 0; i < node->nb_enfants; i++) {
        parser_liberer_ast(node->enfants[i]);
    }
    if (node->condition) parser_liberer_ast(node->condition);
    if (node->bloc_si) parser_liberer_ast(node->bloc_si);
    if (node->bloc_sinon) parser_liberer_ast(node->bloc_sinon);
    free(node->valeur);
    free(node->enfants);
    free(node);
}

void parser_liberer(Parser* parser) {
    free(parser);
}
