SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c -std=c++11


all: $(BIN)/Voraz_maximo $(BIN)/PD_maximo $(BIN)/PD_OperacionesBasicas

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************
$(BIN)/Voraz_maximo: $(SRC)/Voraz_maximo.cpp
	$(CXX) $(CPPFLAGS) -o $(BIN)/Voraz_maximo $(SRC)/Voraz_maximo.cpp

$(BIN)/PD_maximo: $(SRC)/PD_maximo.cpp
	$(CXX) $(CPPFLAGS) -o $(BIN)/PD_maximo $(SRC)/PD_maximo.cpp

$(BIN)/PD_OperacionesBasicas: $(SRC)/PD_OperacionesBasicas.cpp
	$(CXX) $(CPPFLAGS) -o $(BIN)/PD_OperacionesBasicas $(SRC)/PD_OperacionesBasicas.cpp

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
