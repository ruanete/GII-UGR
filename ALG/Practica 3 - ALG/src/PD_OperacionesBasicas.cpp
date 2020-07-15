#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <string>
#include <limits>
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

pair<char,int> minimo(pair<char,int> n, pair<char,int> s, pair<char,int> r, pair<char,int> m, pair<char,int> d) {
    if(n.second <= s.second && n.second <= r.second && n.second <= m.second && n.second <= d.second ) {
        return n;
    } else if (s.second <= r.second && s.second <= m.second && s.second <= d.second) {
        return s;
    } else if (r.second <= m.second && r.second <= d.second) {
        return r;
    } else if (m.second <= d.second) {
        return m;
    } else {
        return d;
    }
}

vector<pair<char,int>> rellenarTabla(vector<vector<pair<char,int>>> &tabla, vector<int> c, int obj){
  int limite_max = std::numeric_limits<int>::max();
  pair<char,int> nada,suma,resta,multiplicacion,division,MINIMO;

  for(unsigned int i = 0; i< tabla[0].size(); i++) {
      tabla[0][i].second = i;
      tabla[0][i].first = ' ';
  }

  for(int i = 1; i < tabla.size(); i++) {
    for( int j = 0; j < tabla[i].size(); j++) {
      if(i==0 || c[i]==0){
        tabla[i][j].first=' ';
        tabla[i][j].second=0;
      }else if(i==0 && c[i]>0){
        tabla[i][j].first=' ';
        tabla[i][j].second=c[i];
      }else if(c[i]<0){
        tabla[i][j].first=' ';
        tabla[i][j].second=limite_max;
      }else{
        nada.first=' ';
        nada.second=tabla[i-1][j].second;

        if(j-c[i] < 0) {
          suma.first = '+';
          suma.second = limite_max;
        } else {
          suma.first = '+';
          suma.second = tabla[i-1][j-c[i]].second;
        }

        if(j+c[i] >= tabla[0].size()){
          resta.first = '-';
          resta.second = limite_max;
        }else{
          resta.first = '-';
          resta.second = tabla[i-1][j+c[i]].second;
        }

        if(j*c[i] >= tabla[0].size()) {
          division.first = '/';
          division.second = limite_max;
        } else {
          division.first = '/';
          division.second = tabla[i-1][j*c[i]].second;
        }

        if(j%c[i] != 0) {
          multiplicacion.first = '*';
          multiplicacion.second = limite_max;
        } else {
          multiplicacion.first = '*';
          multiplicacion.second = tabla[i-1][j/c[i]].second;
        }

        tabla[i][j]=minimo(nada,suma,resta,multiplicacion,division);

        //cout << "Posicion (" << i << "-" << j << "): " << nada.second << " - " << suma.second << " - " << resta.second << " - " << multiplicacion.second << " - " << division.second << " minimo: " << tabla[i][j].second << endl;

      }
    }
  }

  vector <pair<char,int> > solucion;

  int i,j;
  i = c.size()-1;
  j = obj;

  while(j != 0 && i != 0) {
    if(tabla[i-1][j].second == tabla[i][j].second) {
      i = i -1;
    } else {
      solucion.push_back(make_pair(tabla[i][j].first, c[i]));
      if(tabla[i][j].first == '-')
        j = j+c[i];
      else if(tabla[i][j].first == '+')
        j = j-c[i];
      else if(tabla[i][j].first == '*')
        j = j/c[i];
      else if(tabla[i][j].first == '/')
        j = j*c[i];
      else
        j = j-1;

      i = i - 1;
    }
  }

  return solucion;
}

void imprimir(vector<vector<pair<char,int> > > tabla_solucion, vector<int> candidatos, vector<pair<char,int> >sol,int objetivo) {
    cout << "\n ---> Matriz solución:\n\n";

    cout << "      ";
    for ( unsigned int i = 0 ; i < tabla_solucion[0].size() ; i++ ) {
        cout <<  setw(5) << " m=" + to_string(i);
    }

    cout << endl;

    for ( unsigned int i = 0 ; i < tabla_solucion.size() ; i++ ) {
        cout << left << setw(8) << "k = " + to_string(candidatos[i]);
        for( unsigned int j = 0; j < tabla_solucion[i].size(); j++) {
            cout <<setw(4) << tabla_solucion[i][j].first + to_string(tabla_solucion[i][j].second) << " ";
        }
        cout << endl;
    }

    cout << "\nObjetivo: " << objetivo;
    cout << "\nSolucion: { ";
    int obtenido = 0;
    for (int i = 0; i < sol.size(); i++) {
        if(i == sol.size()-1) {
            cout <<" " << sol[i].second  << " ";
            obtenido = sol[i].second;
        } else {
            cout << sol[i].second <<" " << sol[i].first  << " ";
        }
    }

    cout << "} " << endl;
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
  for(int i=0;i<S.size();i++){
    cout << S[i] << " ";
  }

  cout << endl;

  int max = *max_element(S.begin(), S.end());

  vector<vector<pair<char,int> > > tabla_solucion(S.size());
  for ( unsigned int i = 0 ; i < S.size() ; i++ )
    tabla_solucion[i].resize(max*M+1);

  vector <pair <char,int> > sol = rellenarTabla(tabla_solucion,S,M);

  imprimir(tabla_solucion,S,sol,M);

  //EJECUCIÓN PARA SCRIPT Y CALCULAR TIEMPOS//
  /*int max = *max_element(S.begin(), S.end());
  vector<vector<pair<char,int> > > tabla_solucion(S.size());
  for ( unsigned int i = 0 ; i < S.size() ; i++ )
    tabla_solucion[i].resize(max*M+1);

  high_resolution_clock::time_point start, end;
  duration<double> tiempo_transcurrido;
  start = high_resolution_clock::now();

  vector <pair <char,int> > sol = rellenarTabla(tabla_solucion,S,M);

  end = high_resolution_clock::now();
  tiempo_transcurrido = duration_cast<duration<double> >(end - start);
  cout << M << "\t" <<tiempo_transcurrido.count() << endl;*/
}
