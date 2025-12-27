#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "lexer.h"
#include "parser.h"
#include "semantic.h"

// Fonction pour lire le contenu d'un fichier
char* lire_fichier(const char* nom_fichier) {
    FILE* file = fopen(nom_fichier, "rb");
    if (!file) {
        fprintf(stderr, "Erreur: impossible d'ouvrir le fichier '%s'\n", nom_fichier);
        return NULL;
    }
    
    // Determiner la taille du fichier
    fseek(file, 0, SEEK_END);
    long taille = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Allouer la memoire et lire le contenu
    char* source = malloc(taille + 1);
    if (!source) {
        fprintf(stderr, "Erreur: allocation memoire echouee\n");
        fclose(file);
        return NULL;
    }
    
    size_t lue = fread(source, 1, taille, file);
    source[lue] = '\0';
    
    fclose(file);
    return source;
}

int main(int argc, char* argv[]) {
    // Configuration locale pour UTF-8
    setlocale(LC_ALL, "C.UTF-8");
    
    printf("=== Compilateur GALANT ===\n");
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier.gal>\n", argv[0]);
        return 1;
    }
    
    // Lire le fichier source
    printf("Fichier: %s\n", argv[1]);
    char* source = lire_fichier(argv[1]);
    if (!source) {
        return 1;
    }
    
    // Afficher le code source
    printf("\n=== Code Source ===\n");
    printf("%s\n", source);
    //fflush(stdout);
    
    // Phase 1: Analyse Lexicale
    printf("\n[v0] Demarrage de l'analyse lexicale\n");
    //fflush(stdout);
    
    Lexer* lexer = lexer_creer(source);
    printf("[v0] Lexer cree\n");
    //fflush(stdout);
    
    lexer_analyser(lexer);
    printf("[v0] Lexer analyse\n");
    //fflush(stdout);
    
    lexer_afficher_tokens(lexer);
    printf("\n[v0] Analyse lexicale terminee. Tokens: %d\n\n", lexer->nb_tokens);
    //fflush(stdout);
    
    // Phase 2: Analyse Syntaxique
    printf("[v0] Demarrage de l'analyse syntaxique\n");
    //fflush(stdout);
    
    Parser* parser = parser_creer(lexer);
    printf("[v0] Parser cree\n");
    //fflush(stdout);
    
    ASTNode* ast = parser_analyser(parser);
    printf("[v0] AST genere\n");
    //fflush(stdout);
    
    printf("\n=== Analyse Syntaxique (AST) ===\n");
    parser_afficher_ast(ast, 0);
    printf("\n[v0] Analyse syntaxique terminee\n\n");
    //fflush(stdout);
    
    // Phase 3: Analyse Semantique et Execution
    printf("[v0] Demarrage de l'analyse semantique et execution\n");
    //fflush(stdout);
    
    Environnement* env = semantic_creer_env();
    printf("[v0] Environnement cree\n");
    //fflush(stdout);
    
    semantic_executer(env, ast);
    printf("[v0] Execution terminee\n");
    //fflush(stdout);
    
    // Liberer la memoire
    printf("\n[v0] Liberation de la memoire...\n");
    //fflush(stdout);
    
    semantic_liberer_env(env);
    parser_liberer_ast(ast);
    parser_liberer(parser);
    lexer_liberer(lexer);
    free(source);
    
    printf("[v0] Compilation terminee avec succes!\n");
    //fflush(stdout);
    
    return 0;
}
