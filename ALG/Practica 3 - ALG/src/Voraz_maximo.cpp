#include <iostream>
#include <chrono>
#include <time.h>
#include <fstream>
#include <vector>

using namespace std;
using namespace std::chrono;

void sintaxis(){
  cerr << "Sintaxis:" << endl;
  cerr << "  S: Fichero con el conjunto de numeros" << endl;
  cerr << "  M: Valor que queremos obtener (>0)" << endl;
  cerr << "El fichero debe de existir." << endl;
  exit(EXIT_FAILURE);
}

int Seleccion(vector<int>& c){
  int n = c.size();
  int max = numeric_limits<int>::min();
  int pos = -1;

  for (int i=0;i<n;i++){
    if(max<c[i]){
      max = c[i];
      pos = i;
    }
  }
  c.erase(c.begin()+pos);
  return max;
}

bool Factible(int x, int s, int M){
  if(s+x<=M)
    return true;

  return false;
}

pair<vector<int>,int> MaximoVoraz(vector<int> S, int M){
  pair<vector<int>,int> resultado;
  vector<int> c = S;
  int cantidadActual=0;
  int x=0;
  vector<int> s;
  while(cantidadActual < M && c.size()>0){
    x = Seleccion(c);
    if(Factible(x,cantidadActual, M)){
      s.push_back(x);
      cantidadActual+=x;
    }
  }

  resultado.first = s;
  resultado.second = cantidadActual;

  return resultado;
}

int main(int argc, char * argv[]){
  if (argc!=3)
    sintaxis();
  string fichero=argv[1];
  int M=atoi(argv[2]);
  ifstream fd(fichero, std::ifstream::in);
  char linea[50];
  vector<int> conjuntoS;

  if (!fd.is_open() || M<=0)
    sintaxis();

  while(!fd.eof()){
    fd.getline(linea,50);
    conjuntoS.push_back(atoi(linea));
  }


  //EJECUCIÓN EN PANTALLA//
  cout << "Conjunto de valores posibles: ";
  for(int i=0; i<conjuntoS.size();i++)
    cout << conjuntoS[i] << " ";

  pair<vector<int>,int> maximo = MaximoVoraz(conjuntoS, M);

  cout << endl << "Maximo encontrado: " << maximo.second << endl;
  cout << "Conjunto formado por la suma de los siguiente valores: ";
  for(int i=0; i<maximo.first.size();i++)
    cout << maximo.first[i] << " ";

  cout << endl;


  //EJECUCIÓN PARA SCRIPT Y CALCULAR TIEMPOS//
/*
  high_resolution_clock::time_point start, end;
  duration<double> tiempo_transcurrido;
  start = high_resolution_clock::now();

  pair<vector<int>,int> maximo = MaximoVoraz(conjuntoS, M);

  end = high_resolution_clock::now();
  tiempo_transcurrido = duration_cast<duration<double> >(end - start);
  cout << M << "\t" <<tiempo_transcurrido.count() << endl;*/
}
