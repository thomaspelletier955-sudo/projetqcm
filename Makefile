CC     = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

SRC_DIR = src
OBJ_DIR = obj
TARGET  = qcm_tekien

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(OBJ_DIR) qcm $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

qcm:
	mkdir -p qcm

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "  Compilation reussie -> ./$(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
