CXX = g++
CXXFLAGS = -std=c++11

# Liste des fichiers source
SRCS = main.cpp ModelManager.cpp PlaneModel.cpp SphereModel.cpp

# Liste des fichiers objets générés
OBJS = $(SRCS:.cpp=.o)

# Nom du fichier exécutable
TARGET = ransac_example

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)