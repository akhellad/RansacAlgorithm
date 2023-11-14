# Variables
CC := g++
CFLAGS := -std=c++11 -I/usr/include/eigen3 -Iincludes -O2
LDFLAGS := -larmadillo -lblas -llapack
SRC_DIR := srcs
OBJ_DIR := obj
BIN_DIR := .

# Nom de l'exécutable
EXEC := Ransac

# Trouver tous les fichiers source (.cpp) dans SRC_DIR
SRC := $(wildcard $(SRC_DIR)/*.cpp)

# Remplacer chaque fichier source par son fichier objet correspondant dans OBJ_DIR
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Règles
all: $(BIN_DIR)/$(EXEC)

$(BIN_DIR)/$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p results
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf results

fclean: clean
	rm -f $(BIN_DIR)/$(EXEC)

re: fclean all

.PHONY: all clean fclean re
