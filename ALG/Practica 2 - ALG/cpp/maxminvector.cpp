#include <iostream>
#include <chrono>
#include <time.h>

using namespace std;
using namespace std::chrono;

void sintaxis()
{
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño del vector (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se genera un vector de tamaño TAM con elementos aleatorios en [0,VMAX[" << endl;
  exit(EXIT_FAILURE);
}

pair <int,int> Max_Min(int *v, int n){
  pair<int,int> resultado, p1, p2;
  if(n==1){
    resultado.first = v[0];
    resultado.second = v[0];
  }else if(n==2){
    if(v[0]>v[1]){
      resultado.first=v[0];
      resultado.second=v[1];
    }else{
      resultado.first=v[1];
      resultado.second=v[0];
    }
  }else{
    p1=Max_Min(v,n/2);
    p2=Max_Min(v+n/2,n-n/2);

    if(p1.first>p2.first)
      resultado.first = p1.first;
    else
      resultado.first = p2.first;

    if(p1.second<p2.second)
      resultado.second = p1.second;
    else
      resultado.second = p2.second;
    }

  return resultado;
}

int main(int argc, char * argv[])
{
  if (argc!=3)
    sintaxis();
  int tam=atoi(argv[1]);
  int vmax=atoi(argv[2]);
  if (tam<=0 || vmax<=0)
    sintaxis();

  int *v=new int[tam];
  pair<int, int> max_min;

  srand(time(0));
  for (int i=0; i<tam; i++)
   v[i] = rand() % vmax;

  //cout << "Maximo: " << max_min.first << endl;
  //cout << "Minimo: " << max_min.second << endl;

  high_resolution_clock::time_point start, end;
	duration<double> tiempo_transcurrido;

	start = high_resolution_clock::now();

  pair<int,int> p;
  max_min = Max_Min(v,tam);

  end = high_resolution_clock::now();

	tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

	cout << tam << "\t" << tiempo_transcurrido.count() << endl;
}
