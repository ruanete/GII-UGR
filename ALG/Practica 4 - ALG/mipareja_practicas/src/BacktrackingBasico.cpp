#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <chrono>

#include "Apermutacion.h"
#include "MatrizDiscrepancias.h"


using namespace std::chrono;


int Suma_Discrepancias(const Apermutacion &P, const vector <vector<int>> &B) {
    int suma = 0;
    int i = 0;
    Apermutacion::const_iterator it;

    for (it = P.begin(); it != P.end(); ++it) {
        if (i != *it - 1)
            suma += B[i][*it - 1];
        ++i;
    }

    return suma;
}

int asignParejas(int n, Apermutacion &ab, const vector <vector<int>> &D) {
    Apermutacion P(n);
    bool seguir = true;
    int bact = 0;
    int best_discrepancia = numeric_limits<int>::max();
    unsigned int nodos_recorridos = 0;
    while (seguir) {

        nodos_recorridos++;
        bact = Suma_Discrepancias(P, D);

        if (P.GetLevel() == n - 1) {
            if (bact < best_discrepancia) {
                best_discrepancia = bact;
                ab = P;
                seguir = P.Backtracking();
            } else seguir = P.GeneraSiguienteProfundidad();
        } else seguir = P.GeneraSiguienteProfundidad();

    }

    int total = P.NumeroSecuenciasPosibles();

     cout << "Numero de nodos recorridos " << nodos_recorridos
          << " ,total nodos " << total
          << " ,Porcentaje " << (nodos_recorridos / (double) total) * 100.0 << endl;

    return best_discrepancia;
}

void printSolucion(const Apermutacion &P) {
    int i = 1;
    Apermutacion::const_iterator it;

    for (it = P.begin(); it != P.end(); ++it) {
        cout << "Persona: " << i << " con persona: " << *it << endl;
        i++;
    }
}

void sintaxis() {
    cerr << "Sintaxis:" << endl;
    cerr << "  ./bactb archivo_gustos.txt" << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {


    //PARA MEDIR TIEMPOS
    if (argc!=2)
        sintaxis();
    int tam = atoi(argv[1]);

    vector <vector<int>> matriz = matrizDiscrepanciasTiempos(tam);
    Apermutacion P(matriz.size());
    high_resolution_clock::time_point start, end;
    duration<double> tiempo_transcurrido;
    start = high_resolution_clock::now();
    int discrepancia = asignParejas(matriz.size(), P, matriz);
    end = high_resolution_clock::now();
    tiempo_transcurrido = duration_cast<duration<double> >(end - start);
    cout << tam << "\t" <<tiempo_transcurrido.count() << endl;


/*
    if (argc != 2) {
        sintaxis();
    }

    ifstream f(argv[1]);

    vector <vector<int>> matriz = matrizDiscrepancias(f);
    Apermutacion P(matriz.size());

    int discrepancia = asignParejas(matriz.size(), P, matriz);

    cout << "\nDiscrepancia con Backtraking: " << discrepancia << endl << endl;
    printSolucion(P);*/
}
