#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <chrono>

#include "Apermutacion.h"
#include "MatrizDiscrepancias.h"


using namespace std::chrono;

class nodo {
  public:
    int dactual;
    int CI;
    int DE;
    int CS;
    Apermutacion ab = Apermutacion(1);

    nodo(int d,int ci,int de,int cs, Apermutacion a) {
        dactual = d;
        CI = ci;
        DE = de;
        CS = cs;
        ab = a;
    }

    nodo() { };

    bool operator <(const nodo &n) const {
        return DE > n.DE;
    }
};


int Suma_Discrepancias(const Apermutacion &P, const vector <vector<int>> &B) {
    int suma = 0;
    int i = 0;
    Apermutacion::const_iterator it;

    for (it = P.begin(); it != P.end(); ++it) {
        if( i != *it - 1 && i + 1 < *it) {
            suma += B[i][*it - 1]*2;
        }
        ++i;
    }

    return suma;
}

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


vector<int> getNoAsignados(int i, vector<int> v) {
    vector<int> noAsignados;
    for(int j = 0; j <=i ; j++) {
        if(!contains(v,j)) {
            noAsignados.push_back(j);
        }
    }
    return noAsignados;
}

int cotaSuperior(const vector<vector<int>> &matriz, vector<int> asignados) {
    vector <pair<int, int>> sol;
    vector<int> selec;
    vector<int> noAsignados= getNoAsignados(matriz.size()-1,asignados);
    int max = numeric_limits<int>::max();
    int per1, per2, min;


    for (int i: noAsignados) {
        per1=i;
        min = max;

        if (!contains(selec, per1)) {
            for (int j: noAsignados) {
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

    int disc = 0;
    for (int k = 0; k < sol.size(); ++k) {
        disc += matriz[sol[k].first][sol[k].second];
    }

    return disc;
}

int cotaInferior(const vector<vector<int>> &matriz, vector<int> asignados) {
    vector <pair<int, int>> sol;
    vector<int> noAsignados = getNoAsignados(matriz.size()-1,asignados);

    int max = numeric_limits<int>::max();
    int per1, per2, min;

    for (int i :noAsignados) {
        per1 = i;
        min = max;

        for (int j  :noAsignados) {
            if (matriz[per1][j] < min) {
                per2 = j;
                min = matriz[per1][per2];
            }
        }
        sol.push_back(make_pair(per1, per2));
    }

    int disc = 0;
    for (int k = 0; k < sol.size(); ++k) {
        disc += matriz[sol[k].first][sol[k].second];
    }

    return disc;
}

vector<int> obtenerAsignaciones(const Apermutacion &P) {
    vector<int> asignados;
    Apermutacion::const_iterator it;

    for (it = P.begin(); it != P.end(); ++it) {
        if ( *it != 0 )
            asignados.push_back(*it-1);
    }

    int i = P.GetLevel();

    while(i>=0) {
        asignados.push_back(i);
        --i;
    }

    return asignados;
}

int asignParejas(int n, Apermutacion &ab, const vector <vector<int>> &D) {
    Apermutacion P(n);

    int dactual = 0;
    int best_discrepancia = numeric_limits<int>::max();

    vector<int> aux;
    vector<int> asignados(0);

    int CI = cotaInferior(D,asignados);
    int CS = cotaSuperior(D,asignados);
    int C = CS;
    int DE = (CI+CS)/2;

    int nodos_recorridos = 0;
    priority_queue<nodo> pq;

    nodo a(dactual,CI,DE,CS,P);
    pq.push(a);

    do {
        nodos_recorridos++;
        nodo a = pq.top();  pq.pop();

        vector<vector<int> > hijos = a.ab.GeneraHijos();

        for (int i=0; i< (int)hijos.size(); i++) {

            Apermutacion H (hijos[i],a.ab.GetLevel()+1);

            dactual=Suma_Discrepancias(H,D);
            aux = obtenerAsignaciones(H);

            CI= dactual+cotaInferior(D,aux);
            CS= dactual+cotaSuperior(D,aux);
            DE= (CS+CI)/2;

            if (H.GetLevel()==n-1 && dactual<best_discrepancia) {
                ab=H;
                best_discrepancia=dactual;
                C=(C>dactual)?dactual: C;
            } else {
                if (CI<=C ) {
                    nodo anew (dactual,CI,DE,CS,H);
                    pq.push(anew);
                    C= (C>CS)? CS:C;
                }
            }
        }

    } while (!pq.empty());

    int total=ab.NumeroSecuenciasPosibles();
    cout<<"Numero de nodos recorridos "<<nodos_recorridos<< " total nodos "
        <<total<<" Porcentaje "<<(nodos_recorridos/(double)total)*100.0<<endl;
    return best_discrepancia;
}


void printSolucion(const Apermutacion &P) {
    int i = 1;
    Apermutacion::const_iterator it;

    vector<pair<int,int>> aux;

    for (it = P.begin(); it != P.end(); ++it) {
        cout << "Persona: " << i << " con persona: " << *it << endl;
        aux.push_back(make_pair(*it,i));
        i++;
    }
}

void sintaxis() {
    cerr << "Sintaxis:" << endl;
    cerr << "  ./branchandbound archivo_gustos.txt" << endl;
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

   // cout << matriz << endl;

    int discrepancia = asignParejas(matriz.size(), P, matriz);

    cout << "\nDiscrepancia con Branch & Bound: " << discrepancia << endl << endl;

    printSolucion(P);
    */

}
