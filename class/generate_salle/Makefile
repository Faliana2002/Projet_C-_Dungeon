CC = g++ # Le compilateur
CFLAGS = -std=c++11 -Wall # Options du compilateur
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio -lncurses

# Les fichiers source
SRC = ../point.cpp ../rectangle.cpp main.cpp 

# Les fichiers objets
OBJ = $(SRC:.cpp=.o)

# Le nom de l'exécutable
EXEC = generate_lib_map

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
