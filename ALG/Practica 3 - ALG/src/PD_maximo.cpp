#include <iostream>
#include <chrono>
#include <time.h>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void sintaxis(){
  cerr << "Sintaxis:" << endl;
  cerr << "  S: Fichero con el conjunto de numeros" << endl;
  cerr << "  M: Valor que queremos obtener (>0)" << endl;
  cerr << "El fichero debe de existir." << endl;
  exit(EXIT_FAILURE);
}

vector<int> rellenarTabla(vector<vector<int> > &tabla, vector<int> c, int obj) {
    for(unsigned int i = 0; i< tabla[0].size(); i++) {
        tabla[0][i] = 0;
    }

    for(unsigned int i = 0; i < tabla.size(); i++) {
        for( unsigned int j = 0; j < tabla[i].size(); j++) {
          if(i==0 || c[i]==0){
            tabla[i][j] = 0;
          }else if(i<0 || c[i]<0){
            tabla[i][j] = numeric_limits<int>::min();
          }else if (c[i] > int(j)) {
              tabla[i][j] = tabla[i-1][j];
          }else{
            tabla[i][j] = max(tabla[i-1][j], c[i] + tabla[i-1][j-c[i]]);
          }
        }
    }

    vector <int> solucion;

    int i,j;
    i = c.size()-1;
    j = obj;

    //recomponer la solución
    while(j != 0 && i != 0) {
        if(tabla[i-1][j] == tabla[i][j]) {
            i = i -1;
        } else {
            solucion.push_back(c[i]);
            j = j-c[i];
            i = i -1;
        }
    }

    return solucion;
}

void imprimir(vector<vector<int> > tabla_solucion, vector<int> candidatos, vector<int> sol,int objetivo) {
    cout << "\n ---> Matriz solución:\n\n";

    cout << "      ";
    for ( unsigned int i = 0 ; i < tabla_solucion[0].size() ; i++ ) {
        cout <<  setw(5) << " m=" + to_string(i);
    }

    cout << endl;

    for ( unsigned int i = 0 ; i < tabla_solucion.size() ; i++ ) {
        cout << left << setw(8) << "k = " + to_string(candidatos[i]);
        for( unsigned int j = 0; j < tabla_solucion[i].size(); j++) {
            cout <<setw(4) << tabla_solucion[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nObjetivo: " << objetivo;
    cout << "\nSolucion: { ";
    int obtenido = 0;
    for(int i: sol) {
        cout << i << " ";
        obtenido+=i;
    }
    cout << "} == " <<obtenido << endl;
}

int main(int argc, char * argv[]){
  if (argc!=3)
    sintaxis();
  string fichero=argv[1];
  int M=atoi(argv[2]);
  ifstream fd(fichero, std::ifstream::in);
  char linea[50];
  vector<int> S, solucion;

  if (!fd.is_open() || M<=0)
    sintaxis();

  S.push_back(0);

  while(!fd.eof()){
    fd.getline(linea,50);
    S.push_back(atoi(linea));
  }

  S.pop_back();

  //EJECUCIÓN EN PANTALLA//
  cout << "Valor al que queremos llegar: " << M << endl;
  cout << "Valores posibles para sumar: ";
  for(int i=1;i<S.size();i++){
    cout << S[i] << " ";
  }

  cout << endl;

  vector<vector<int> > tabla_solucion(S.size());
  for ( unsigned int i = 0 ; i < S.size() ; i++ )
    tabla_solucion[i].resize(M+1);

  vector <int> sol= rellenarTabla(tabla_solucion,S,M);

  imprimir(tabla_solucion,S,sol,M);

  //EJECUCIÓN PARA SCRIPT Y CALCULAR TIEMPOS//
  /*
  vector<vector<int> > tabla_solucion(S.size());
  for ( unsigned int i = 0 ; i < S.size() ; i++ )
    tabla_solucion[i].resize(M+1);

  high_resolution_clock::time_point start, end;
  duration<double> tiempo_transcurrido;
  start = high_resolution_clock::now();

  vector <int> sol= rellenarTabla(tabla_solucion,S,M);

  end = high_resolution_clock::now();
  tiempo_transcurrido = duration_cast<duration<double> >(end - start);
  cout << M << "\t" <<tiempo_transcurrido.count() << endl;*/
}
