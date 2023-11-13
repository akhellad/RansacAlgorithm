CC=g++
CFLAGS=-std=c++11 -I/usr/include/eigen3
LDFLAGS=-larmadillo -lblas -llapack
OBJ=main.o ModelManager.o PlaneModel.o SphereModel.o

# Nom du fichier exécutable
EXEC=ransac_example

all:	$(EXEC)

$(EXEC):	$(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o:	%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re:	fclean all

.PHONY:	all clean fclean re