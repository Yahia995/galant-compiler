CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = galant-compiler
SOURCES = main.c lexer.c parser.c semantic.c
OBJECTS = $(SOURCES:.c=.o)

# Compilateur GALANT - GALe LAnguage educaTif (.gal)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)
	@echo "Compilation reussie. Executable: $(TARGET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "  Compile: $<"

clean:
	@rm -f $(OBJECTS) $(TARGET)
	@echo "Nettoyage effectue"

run: all
	@echo "\n=== Execution de programme.gal ===\n"
	@./$(TARGET) programme.gal

help:
	@echo "Commandes disponibles:"
	@echo "  make          - Compiler le projet"
	@echo "  make clean    - Nettoyer les fichiers compiles"
	@echo "  make run      - Compiler et executer programme.gal"
	@echo "  make help     - Afficher cette aide"

.PHONY: all clean run help
