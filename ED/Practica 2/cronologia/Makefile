SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c


all: $(BIN)/pruebacronologia

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************
$(BIN)/pruebacronologia : $(OBJ)/pruebacronologia.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o
	$(CXX) -o $(BIN)/pruebacronologia $(OBJ)/pruebacronologia.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o

$(OBJ)/pruebacronologia.o : $(INC)/Cronologia.h $(INC)/FechaHistorica.h $(SRC)/pruebacronologia.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/pruebacronologia.o $(SRC)/pruebacronologia.cpp

$(OBJ)/Cronologia.o : $(INC)/Cronologia.h $(INC)/FechaHistorica.h $(SRC)/Cronologia.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/Cronologia.o $(SRC)/Cronologia.cpp

$(OBJ)/FechaHistorica.o : $(INC)/FechaHistorica.h $(SRC)/FechaHistorica.cpp $(INC)/VectorDinamico.h $(SRC)/VectorDinamico.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/FechaHistorica.o $(SRC)/FechaHistorica.cpp

# ************ Limpieza ************
clean :
	echo "Limpiando..."
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~
	echo "Limpieza finalizada."

mrproper : clean
	-rm $(BIN)/* doc/html/*
