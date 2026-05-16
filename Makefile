CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

# 1. On liste nos fichiers source à la main
SRCS = src/main.c src/qcm.c 
# 2. On dit que les fichiers .o iront dans le dossier obj/
OBJS = obj/main.o obj/qcm.o

TARGET = qcm_tekien

# Règle principale
all: obj qcm $(TARGET)

# Création des dossiers si nécessaires
obj:
	mkdir -p obj

qcm:
	mkdir -p qcm

# Compilation du programme final (liaison des .o)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Compilation reussie -> ./$(TARGET)"

# Règle simple pour transformer un .c en .o
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

# Nettoyage
clean:
	rm -rf obj qcm $(TARGET)

# Exécution
run: all
	./$(TARGET)

.PHONY: all clean run
