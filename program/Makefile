CC = g++ # Le compilateur
CFLAGS = -std=c++11 -Wall # Options du compilateur
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio -lncurses

# # Les fichiers source
# SRC = ../class/Salles-test/Salles.cpp ../class/Personnages/BarreVie.cpp ../class/Personnages/Joueur.cpp ../class/Personnages/Ennemi.cpp  ../class/Armes/CorpsaCorps.cpp ../class/Armes/Distance.cpp ../class/Armes/Projectile.cpp ../class/point.cpp ../class/rectangle.cpp ../class/Gestion.cpp main.cpp 

# # Les fichiers objets
# OBJ = $(SRC:.cpp=.o)

# # Le nom de l'exécutable
# EXEC = jeu

# all: $(EXEC)

# $(EXEC): $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LIBS)

# %.o: %.cpp
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJ) $(EXEC)


# Fichiers source pour l'application principale
SRC = ../class/Salles-test/Salles.cpp ../class/Personnages/BarreVie.cpp ../class/Personnages/Joueur.cpp ../class/Personnages/Ennemi.cpp  ../class/Armes/CorpsaCorps.cpp ../class/Armes/Distance.cpp ../class/Armes/Projectile.cpp ../class/point.cpp ../class/rectangle.cpp ../class/Gestion.cpp main.cpp 

# Fichiers source pour les tests
TEST_SRC = ../class/TestArmes.cpp $(filter-out main.cpp, $(SRC))

# Fichiers objets pour l'application et les tests
OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Noms des exécutables pour l'application et les tests
EXEC = jeu
TEST_EXEC = test_jeu

all: $(EXEC) $(TEST_EXEC)

# Règle pour compiler l'exécutable principal
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LIBS)

# Règle pour compiler et exécuter les tests
$(TEST_EXEC): $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_EXEC) $(LIBS)
	./$(TEST_EXEC)

# Règle de compilation générique
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) $(TEST_OBJ) $(TEST_EXEC)