SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++ -std=c++11
CPPFLAGS =  -pg  -I$(INC) -c
CPPFLAGS2 =  -pg

HDRS = $(INC)/*.h

all:  $(BIN)/prueba_APermutacion $(BIN)/Voraz $(BIN)/BacktrackingBasico $(BIN)/BacktrackingPoda $(BIN)/BranchAndBound

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************

$(BIN)/Voraz: $(OBJ)/MatrizDiscrepancias.o $(OBJ)/Voraz.o
	$(CXX) $(CPPFLAGS2) $^ -o $@

$(BIN)/BacktrackingBasico: $(OBJ)/MatrizDiscrepancias.o $(OBJ)/Bactb.o $(OBJ)/Apermutacion.o
	$(CXX) $(CPPFLAGS2) $^ -o $@

$(BIN)/BacktrackingPoda: $(OBJ)/MatrizDiscrepancias.o $(OBJ)/Bactp.o $(OBJ)/Apermutacion.o
	$(CXX) $(CPPFLAGS2) $^ -o $@

$(BIN)/BranchAndBound: $(OBJ)/MatrizDiscrepancias.o $(OBJ)/BranchAndBound.o $(OBJ)/Apermutacion.o
	$(CXX) $(CPPFLAGS2) $^ -o $@

$(BIN)/prueba_APermutacion: $(OBJ)/Apermutacion.o $(OBJ)/prueba_APermutacion.o
	$(CXX) $(CPPFLAGS2) $^ -o $@

$(OBJ)/Voraz.o: $(SRC)/Voraz.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/MatrizDiscrepancias.o: $(SRC)/MatrizDiscrepancias.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/Bactb.o: $(SRC)/BacktrackingBasico.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/Bactp.o: $(SRC)/BacktrackingPoda.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/prueba_APermutacion.o: $(SRC)/prueba_APermutacion.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/Apermutacion.o: $(SRC)/Apermutacion.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/BranchAndBound.o: $(SRC)/BranchAndBound.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@
# ************ Limpieza ************
clean :
	-rm $(OBJ)/*.o $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
