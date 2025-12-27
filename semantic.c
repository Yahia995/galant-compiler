#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global error flag
static int error_flag = 0;

Environnement* semantic_creer_env(void) {
    Environnement* env = malloc(sizeof(Environnement));
    env->nb_variables = 0;
    error_flag = 0;
    return env;
}

Variable* semantic_trouver_variable(Environnement* env, const char* nom) {
    for (int i = 0; i < env->nb_variables; i++) {
        if (strcmp(env->variables[i].nom, nom) == 0) {
            return &env->variables[i];
        }
    }
    return NULL;
}

void semantic_definir_variable(Environnement* env, const char* nom, int valeur) {
    Variable* var = semantic_trouver_variable(env, nom);
    if (var) {
        var->valeur = valeur;
        var->initialise = 1;
    } else {
        if (env->nb_variables >= MAX_VARIABLES) {
            fprintf(stderr, "Erreur semantique: nombre maximum de variables atteint\n");
            fflush(stderr);
            error_flag = 1;
            return;
        }
        var = &env->variables[env->nb_variables++];
        var->nom = malloc(strlen(nom) + 1);
        strcpy(var->nom, nom);
        var->valeur = valeur;
        var->initialise = 1;
    }
}

void semantic_declarer_variable(Environnement* env, const char* nom) {
    Variable* var = semantic_trouver_variable(env, nom);
    if (var) {
        // Variable already exists, nothing to do
        return;
    }
    
    if (env->nb_variables >= MAX_VARIABLES) {
        fprintf(stderr, "Erreur semantique: nombre maximum de variables atteint\n");
        fflush(stderr);
        error_flag = 1;
        return;
    }
    
    var = &env->variables[env->nb_variables++];
    var->nom = malloc(strlen(nom) + 1);
    strcpy(var->nom, nom);
    var->valeur = 0;  // Default value
    var->initialise = 0;  // Mark as uninitialized
}

static int evaluer_expression(Environnement* env, ASTNode* node) {
    if (!node) return 0;
    
    if (node->type == AST_NOMBRE) {
        return node->nombre;
    }
    
    if (node->type == AST_VARIABLE) {
        Variable* var = semantic_trouver_variable(env, node->valeur);
        if (!var) {
            fprintf(stderr, "Erreur semantique: variable '%s' non declaree\n", node->valeur);
            fflush(stderr);
            error_flag = 1;
            return 0;
        }
        if (!var->initialise) {
            fprintf(stderr, "Erreur semantique: variable '%s' utilisee avant initialisation\n", node->valeur);
            fflush(stderr);
            error_flag = 1;
            return 0;
        }
        return var->valeur;
    }
    
    if (node->type == AST_OPERATEUR) {
        if (node->nb_enfants < 2) return 0;
        
        int gauche = evaluer_expression(env, node->enfants[0]);
        int droit = evaluer_expression(env, node->enfants[1]);
        
        if (strcmp(node->valeur, "+") == 0) return gauche + droit;
        if (strcmp(node->valeur, "-") == 0) return gauche - droit;
        if (strcmp(node->valeur, "*") == 0) return gauche * droit;
        if (strcmp(node->valeur, "/") == 0) {
            if (droit == 0) {
                fprintf(stderr, "Erreur semantique: division par zero\n");
                fflush(stderr);
                error_flag = 1;
                return 0;
            }
            return gauche / droit;
        }
        if (strcmp(node->valeur, "%") == 0) {
            if (droit == 0) {
                fprintf(stderr, "Erreur semantique: modulo par zero\n");
                fflush(stderr);
                error_flag = 1;
                return 0;
            }
            return gauche % droit;
        }
    }
    
    if (node->type == AST_CONDITION_EXPR) {
        if (node->nb_enfants < 2) return 0;
        
        int gauche = evaluer_expression(env, node->enfants[0]);
        int droit = evaluer_expression(env, node->enfants[1]);
        
        if (strcmp(node->valeur, "==") == 0) return gauche == droit;
        if (strcmp(node->valeur, "!=") == 0) return gauche != droit;
        if (strcmp(node->valeur, ">") == 0) return gauche > droit;
        if (strcmp(node->valeur, "<") == 0) return gauche < droit;
        if (strcmp(node->valeur, ">=") == 0) return gauche >= droit;
        if (strcmp(node->valeur, "<=") == 0) return gauche <= droit;
    }
    
    return 0;
}

static void executer_noeud(Environnement* env, ASTNode* node) {
    if (!node || error_flag) return;
    
    switch (node->type) {
        case AST_PROGRAMME:
        case AST_BLOC:
            for (int i = 0; i < node->nb_enfants; i++) {
                executer_noeud(env, node->enfants[i]);
                if (error_flag) return;  // Stop on error
            }
            break;
        
        case AST_AFFECTATION: {
            // Check if this is a declaration without initialization
            if (node->nb_enfants == 0) {
                semantic_declarer_variable(env, node->valeur);
            } else {
                // Declaration with initialization OR reassignment
                int valeur = evaluer_expression(env, node->enfants[0]);
                if (error_flag) return;
                semantic_definir_variable(env, node->valeur, valeur);
            }
            break;
        }
        
        case AST_AFFICHAGE: {
            int valeur = evaluer_expression(env, node->enfants[0]);
            if (!error_flag) {
                printf("%d\n", valeur);
            }
            break;
        }
        
        case AST_CONDITION: {
            int condition = evaluer_expression(env, node->condition);
            if (error_flag) return;
            if (condition) {
                executer_noeud(env, node->bloc_si);
            } else if (node->bloc_sinon) {
                executer_noeud(env, node->bloc_sinon);
            }
            break;
        }
        
        case AST_BOUCLE: {
            while (evaluer_expression(env, node->condition) && !error_flag) {
                executer_noeud(env, node->bloc_si);
            }
            break;
        }
        
        default:
            break;
    }
}

int semantic_evaluer(Environnement* env, ASTNode* node) {
    return evaluer_expression(env, node);
}

void semantic_executer(Environnement* env, ASTNode* programme) {
    printf("\n=== Execution ===\n");
    executer_noeud(env, programme);
}

void semantic_liberer_env(Environnement* env) {
    for (int i = 0; i < env->nb_variables; i++) {
        free(env->variables[i].nom);
    }
    free(env);
}