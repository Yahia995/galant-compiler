CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = galant-compiler
SOURCES = main.c lexer.c parser.c semantic.c
OBJECTS = $(SOURCES:.c=.o)

# Compilateur GALANT - GALe LAnguage eNducaTif (.gal)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)
	@echo "✓ Compilation réussie. Exécutable: $(TARGET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "  Compilé: $<"

clean:
	@rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Nettoyage effectué"

run: all
	@echo "\n=== Exécution de programme.gal ===\n"
	@./$(TARGET) programme.gal

help:
	@echo "Commandes disponibles:"
	@echo "  make          - Compiler le projet"
	@echo "  make clean    - Nettoyer les fichiers compilés"
	@echo "  make run      - Compiler et exécuter programme.gal"
	@echo "  make help     - Afficher cette aide"

.PHONY: all clean run help
