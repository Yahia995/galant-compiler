# 🚀 GALANT - Compilateur Éducatif

**GALANT** = **GA**Le **LAN**guage educa**T**if

Un compilateur complet en C pour un langage de programmation minimaliste, **entièrement en français**.

## Caractéristiques

- ✅ Syntaxe complètement en français
- ✅ Extension de fichier : `.gal`
- ✅ Architecture complète : Lexer → Parser → Sémantique
- ✅ Support des variables, conditions, boucles, opérateurs
- ✅ Commentaires avec `#`
- ✅ Code C bien structuré et modularisé

## Installation Rapide

\`\`\`bash
make              # Compiler
./galant-compiler programme.gal   # Exécuter
\`\`\`

## Exemple Simple

**programme.gal :**
\`\`\`galant
variable x = 0;
tantque (x < 5) {
  afficher(x);
  x = x + 1;
}
\`\`\`

**Résultat :**
\`\`\`
0
1
2
3
4
\`\`\`

## Mots-Clés

- `variable` - Déclarer une variable
- `afficher` - Afficher une valeur
- `si` / `sinon` - Conditions
- `tantque` - Boucles

## Opérateurs

**Arithmétiques :** `+`, `-`, `*`, `/`, `%`
**Comparaison :** `==`, `!=`, `>`, `<`, `>=`, `<=`

## Documentation

Voir `GUIDE_UTILISATION.md` pour un guide complet avec exemples.

## Architecture

- `lexer.c/h` - Analyse lexicale (tokenization)
- `parser.c/h` - Analyse syntaxique (AST)
- `semantic.c/h` - Sémantique et exécution
- `main.c` - Point d'entrée
- `Makefile` - Compilation

## Licence

Libre d'utilisation à titre éducatif.
