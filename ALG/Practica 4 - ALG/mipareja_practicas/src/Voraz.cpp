#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>
#include <chrono>

#include "MatrizDiscrepancias.h"

using namespace std::chrono;
using namespace std;

bool contains(vector<int> v, int x) {
    if (std::find(v.begin(), v.end(), x) != v.end()) {
        return true;
    } else {
        return false;
    }
}

int buscarPareja(int x, vector <pair<int, int>> v) {
    for (pair<int, int> y: v) {
        if (y.second == x) {
            return y.first;
        }
    }
    return -1;
}

vector <pair<int, int>> asignParejas(vector <vector<int>> matriz) {
    vector <pair<int, int>> sol;
    vector<int> selec;

    int max = numeric_limits<int>::max();
    int per1, per2, min;

    for (per1 = 0; per1 < matriz.size(); ++per1) {
        min = max;

        if (!contains(selec, per1)) {
            for (int j = 0; j < matriz[per1].size(); ++j) {
                if (matriz[per1][j] < min && !contains(selec, j)) {
                    min = matriz[per1][j];
                    per2 = j;
                }
            }
        } else {
            per2 = buscarPareja(per1, sol);
        }

        selec.push_back(per1);
        selec.push_back(per2);
        sol.push_back(make_pair(per1, per2));
    }

    return sol;
};

void sintaxis() {
    cerr << "Sintaxis:" << endl;
    cerr << "  ./voraz archivo_gustos.txt" << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {


    //PARA MEDIR TIEMPOS
    if (argc!=2)
        sintaxis();
    int tam = atoi(argv[1]);
    vector <vector<int>> matriz = matrizDiscrepanciasTiempos(tam);
    high_resolution_clock::time_point start, end;
    duration<double> tiempo_transcurrido;
    start = high_resolution_clock::now();
    vector <pair<int, int>> sol = asignParejas(matriz);
    end = high_resolution_clock::now();
    tiempo_transcurrido = duration_cast<duration<double> >(end - start);
    cout << tam << "\t" <<tiempo_transcurrido.count() << endl;


    /*
    if(argc != 2){
         sintaxis();
     }
     ifstream f(argv[1]);
     vector <vector<int>> matriz = matrizDiscrepancias(f);

     //cout << matriz;

     vector <pair<int, int>> sol = asignParejas(matriz);

     int disc = 0;
     for (int k = 0; k < sol.size(); ++k) {
         disc += matriz[sol[k].first][sol[k].second];
     }

     for (int k = 0; k < sol.size(); ++k) {
         cout << "Persona " << sol[k].first + 1 << ": con persona " << sol[k].second + 1 << endl;
     }

     cout << "Discrepancia voraz total: " << disc << endl;
     */

}
