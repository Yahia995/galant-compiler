#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "parser.h"
#include <stdint.h>

#define MAX_VARIABLES 1000

// Structure pour stocker une variable
typedef struct {
    char* nom;
    int valeur;
    int initialise;
} Variable;

// Structure pour l'environnement d'exécution
typedef struct {
    Variable variables[MAX_VARIABLES];
    int nb_variables;
} Environnement;

// Fonctions du module sémantique
Environnement* semantic_creer_env(void);
int semantic_evaluer(Environnement* env, ASTNode* node);
void semantic_executer(Environnement* env, ASTNode* programme);
Variable* semantic_trouver_variable(Environnement* env, const char* nom);
void semantic_definir_variable(Environnement* env, const char* nom, int valeur);
void semantic_liberer_env(Environnement* env);

#endif
