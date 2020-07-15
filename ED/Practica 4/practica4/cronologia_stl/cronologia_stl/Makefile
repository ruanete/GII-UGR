SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++ -std=c++11
CPPFLAGS = -Wall -g  -I$(INC) -c


all: $(BIN)/pruebacronologia $(BIN)/estadisticaEventos $(BIN)/filtradoPalabraClave $(BIN)/filtradoIntervalo $(BIN)/union_cronologias
# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Compilación de módulos ************
$(BIN)/pruebacronologia : $(OBJ)/pruebacronologia.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o
	$(CXX) -o $(BIN)/pruebacronologia $(OBJ)/pruebacronologia.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o

$(BIN)/estadisticaEventos : $(OBJ)/estadisticaEventos.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o
	$(CXX) -o $(BIN)/estadisticaEventos $(OBJ)/estadisticaEventos.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o

$(BIN)/filtradoIntervalo : $(OBJ)/filtradoIntervalo.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o
	$(CXX) -o $(BIN)/filtradoIntervalo $(OBJ)/filtradoIntervalo.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o

$(BIN)/filtradoPalabraClave : $(OBJ)/filtradoPalabraClave.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o
	$(CXX) -o $(BIN)/filtradoPalabraClave $(OBJ)/filtradoPalabraClave.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o

$(BIN)/union_cronologias : $(OBJ)/union_cronologias.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o
	$(CXX) -o $(BIN)/union_cronologias $(OBJ)/union_cronologias.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o

$(OBJ)/pruebacronologia.o : $(INC)/Cronologia.h $(INC)/FechaHistorica.h $(SRC)/pruebacronologia.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/pruebacronologia.o $(SRC)/pruebacronologia.cpp

$(OBJ)/estadisticaEventos.o : $(INC)/Cronologia.h $(INC)/FechaHistorica.h $(SRC)/estadisticaEventos.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/estadisticaEventos.o $(SRC)/estadisticaEventos.cpp

$(OBJ)/filtradoIntervalo.o : $(INC)/Cronologia.h $(INC)/FechaHistorica.h $(SRC)/filtradoIntervalo.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/filtradoIntervalo.o $(SRC)/filtradoIntervalo.cpp

$(OBJ)/filtradoPalabraClave.o : $(INC)/Cronologia.h $(INC)/FechaHistorica.h $(SRC)/filtradoPalabraClave.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/filtradoPalabraClave.o $(SRC)/filtradoPalabraClave.cpp

$(OBJ)/union_cronologias.o : $(INC)/Cronologia.h $(INC)/FechaHistorica.h $(SRC)/union_cronologias.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/union_cronologias.o $(SRC)/union_cronologias.cpp

$(OBJ)/Cronologia.o : $(INC)/Cronologia.h $(INC)/FechaHistorica.h $(SRC)/Cronologia.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/Cronologia.o $(SRC)/Cronologia.cpp

$(OBJ)/FechaHistorica.o : $(INC)/FechaHistorica.h $(SRC)/FechaHistorica.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/FechaHistorica.o $(SRC)/FechaHistorica.cpp



# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
